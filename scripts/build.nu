#!/usr/bin/env nu

# Builds every build.yaml target with Apple container, the same way ZMK's
# GitHub workflow does, and copies each .uf2 into firmware/.
def main [
  --workspace: string # West workspace kept between builds (default: .zmk-workspace)
] {
  let repo = ($env.FILE_PWD | path dirname)
  let ws = ($workspace | default ($repo | path join ".zmk-workspace") | path expand)
  mkdir $ws ($repo | path join "firmware")
  rm -rf ($ws | path join "config")
  cp -r ($repo | path join "config") $ws

  let builds = (open ($repo | path join "build.yaml") | get include | each {|target|
    let name = ($target | get artifact-name)
    let snippet = if ($target.snippet? | is-empty) { "" } else { $"-S ($target.snippet)" }
    let cmake = ($target.cmake-args? | default "")
    [
      $"west build -p -s zmk/app -d build/($name) -b ($target.board) ($snippet)"
      $"-- -DZMK_CONFIG=/ws/config -DSHIELD='($target.shield)' -DZMK_EXTRA_MODULES=/repo ($cmake)"
      $"&& cp build/($name)/zephyr/zmk.uf2 /repo/firmware/($name).uf2"
    ] | str join " "
  } | str join " && ")

  # The workspace is a bind mount owned by the host user, which git rejects without safe.directory.
  let setup = "git config --global --add safe.directory '*' && { [ -d .west ] || west init -l config; } && west update --fetch-opt=--filter=tree:0 && west zephyr-export"

  (^container run --rm --memory 4g --cpus 4
    --volume $"($ws):/ws" --volume $"($repo):/repo" --workdir /ws
    docker.io/zmkfirmware/zmk-build-arm:stable
    bash -c $"($setup) && ($builds)")
}
