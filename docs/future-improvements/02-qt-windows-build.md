# 02 - Qt Windows Build Compatibility

Status: Planned

Source: `Nicolas01/Gittyup:fix/qt-version-windows-build`

Upstream commits reviewed:
- `814e7ee7` - Bump CI Qt to 6.7.3 to fix Windows build
- `0668cbed` - Fix Qt 6.7 packaging paths/plugins
- `2463ebef` - Install libcups2-dev on Linux CI for Qt 6.7 PrintSupport
- `16a1d637` - Use `QT_ROOT_DIR` for AppImage QTDIR
- `db5e00ee` - Pass `--repo` to `gh release`
- `567925b9` - Re-polish palette through style on Windows
- `78db8d51` - Remove unused Qt PrintSupport module instead of installing CUPS

## Goal

Port only the build and runtime compatibility fixes relevant to GitNortek’s current CI/package setup.

## Current Behavior

GitNortek already has NortekMed packaging workflow changes. The forked branch includes CI fixes for newer Qt/MSVC and packaging plugin path changes that may not all apply directly.

## Desired Behavior

- Windows CI/package build remains compatible with current Qt and MSVC versions.
- Linux packaging does not require unused Qt modules.
- Windows theme colors apply reliably after style changes.

## Implementation Plan

1. Compare `Nicolas01/Gittyup:fix/qt-version-windows-build` against current GitNortek workflows and package files.
2. Port only still-relevant changes.
3. Avoid broad workflow rewrites unless current CI is broken.
4. If runtime Windows palette polishing is still missing, port it separately inside this feature commit.

## Acceptance Criteria

- Local Linux build still succeeds.
- Workflow/package changes are minimal and match current GitNortek workflow names.
- No unused Qt dependency is added.
- Runtime code changes are limited to confirmed Windows style/palette fixes.

## Risk

Low-medium. Mostly CI/package work, but Windows runtime behavior cannot be fully validated from Linux.
