
# Grid → MIDI Backlog

## Epic 0 — Project Foundations
| ID | Story | Done When |
|---|---|---|
|0.1|**Repo bootstrapped** — As a developer, I want a clean Git repo with an MIT licence, `.gitignore`, and an empty `src/` folder so the team has a canonical place to work.|A new Git repo exists on GitHub (or similar) with default branch, README, LICENCE, `.editorconfig`, and CI placeholder.|
|0.2|**Basic CMake scaffold** — As a developer, I can run `cmake .. && make` locally and get a “hello” binary so I know the tool‑chain is wired.|`cmake` config builds on macOS; CI job compiles on Raspberry Pi OR cross‑compile image.|

## Epic 1 — Local Development Environment (macOS)
| ID | Story | Done When |
|---|---|---|
|1.1|**Dependency script** — As a dev, I can run `./scripts/bootstrap_macos.sh` to install Homebrew packages (`libmonome`, `alsa-lib`, `pkg-config`, etc.) so onboarding takes minutes, not hours.|Script installs deps idempotently and README documents usage.|
|1.2|**Cross‑compile option** — As a dev on Apple Silicon, I can build ARM binaries (Pi target) via a documented `toolchain-arm64.cmake` so I don’t need to SSH into the Pi for every build.|`make pi` command produces an executable that runs on the Pi.|

## Epic 2 — Raspberry Pi Runtime Environment
| ID | Story | Done When |
|---|---|---|
|2.1|**Pi image prepared** — As a maintainer, I have a Pi OS image checklist (update, enable SSH, install `libmonome-dev`, `libasound2-dev`, disable HDMI, etc.) so any fresh SD card can run the program.|Markdown guide checked on a clean flash; all packages install without prompts.|
|2.2|**PiSound verification** — As a user, I can run `aconnect -l` and see the PiSound ALSA client so I know MIDI ports are available.|PiSound appears in ALSA client list after reboot.|

## Epic 3 — Core Feature: Note Output
| ID | Story | Done When |
|---|---|---|
|3.1|**Grid press → Note‑On** — Pressing any Grid key sends a MIDI **Note‑On** on channel 10 with velocity 100; mapping is `note = y*16 + x`.|Verified via `aseqdump` or DAW MIDI monitor.|
|3.2|**Grid release → Note‑Off** — Releasing the key sends a matching **Note‑Off** (or Note‑On vel 0) so notes stop sounding.|No stuck notes after frantic button mashing.|

## Epic 4 — System Integration & Deployment
| ID | Story | Done When |
|---|---|---|
|4.1|**Configurable systemd service** — As a performer, I can `sudo systemctl enable --now grid-midi` and the app autostarts on boot so gigs don’t require a terminal.|Service file lives in repo; install step documented.|
|4.2|**Release artifact workflow** — Tagging `v*` in GitHub triggers CI to build a `.tar.gz` (or `.deb`) with binary + service unit so deployments are one‑command.|GitHub Action uploads asset; checksum included.|

## Epic 5 — Developer Experience & Testing
| ID | Story | Done When |
|---|---|---|
|5.1|**Unit tests for MIDI mapping** — Pure‑C tests validate `x,y → note` logic so regressions are caught early.|`ctest` passes locally & in CI.|
|5.2|**Lint & format** — `clang-format` + `clang-tidy` run in CI so codebase stays consistent.|PR fails if code isn’t formatted.|

## Epic 6 — Documentation & Demo
| ID | Story | Done When |
|---|---|---|
|6.1|**README quick‑start** — Step‑by‑step for macOS + Pi: clone, bootstrap, build, run.|New dev can follow docs and see notes in under 15 min.|
|6.2|**Demo video/GIF** — 15‑second screen‑cap or phone clip embedded in README so curious folks grok the project instantly.|Video hosted and referenced via Markdown.|

## Epic 7 — Stretch Goals *(optional after “hello world” works)*
| ID | Story | Done When |
|---|---|---|
|7.1|**LED feedback** — Lit LED on press for visual confirmation.|LED mirrors note state.|
|7.2|**Velocity layers** — Long press or rapid tap influences velocity 30‑120.|Velocity visibly varies in MIDI monitor.|
|7.3|**Dynamic channel select** — Holding a corner key enters “channel mode” letting user pick MIDI channel on the fly.|Channel change persisted until reboot.|

---

### How to use this backlog
1. **Import** — Copy into your tracker; give each story a size/owner.  
2. **Slice if needed** — If a story feels > 1 day, break it down.  
3. **Sprint cadence** — Knock out Epics 0–3 first; you’ll have playable output in one sprint.  
4. **Iterate** — Treat Pi deployment issues as new stories; keep feedback loops tight.
