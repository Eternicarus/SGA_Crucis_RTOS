# Copilot Instructions for SGA_Crucis_RTOS

## ÏîÄ¿¼Ü¹¹






```instructions
# Copilot instructions ¡ª SGA_Crucis_RTOS (concise, actionable)

-- Project snapshot
- Type: STM32 RTOS firmware (Keil/MDK project files included). Modular layering:
  - Driver layer: Driver/Src (prefix: `drv_hal_*`), configuration in `Driver/Inc/drv_hal_conf.h`.
  - Application tasks: `Apply/Task/Inc` (APIs) and `Apply/Task/Src` (implementations). Typical names: `task_*`.
  - BSP / adapters: `Bsp/¡­`, external-device adapters prefixed `ocd_*`.
  - Hardware support: `Hardware/STM32F1XX` (CMSIS/HAL headers present) and project file `Project/STM32.uvprojx`.

-- Quick operational guidance (what an AI agent needs to do)
- To add a new task: create header in `Apply/Task/Inc` (declare APIs) and source in `Apply/Task/Src` (implement). Follow function-style examples in `task_motorsys.h` / `task_motorsys.c`.
- To add or modify a HAL driver: edit `Driver/Src/drv_hal_*.c` and the enable macro in `Driver/Inc/drv_hal_conf.h` (e.g. `DRV_HAL_PWM_ENABLE`). See `Driver/Src/drv_hal_pwm.c` for patterns: init function `Drv_PWM_Init(...)`, runtime setters `Drv_PWM_HighLvTimeSet(...)`, and error handling via `Drv_HAL_Error(__FILE__, __LINE__)`.
- Naming conventions: `task_*` for tasks, `drv_hal_*` for HAL drivers, `ocd_*` for peripheral adapters. Keep Inc/Src parity.

-- Build / flash / debug (developer workflows to call)
- Project contains Keil/MDK files (`Project/STM32.uvprojx`, `.uvoptx`) but VS Code tasks are configured for EIDE. Common task labels available in workspace:
  - `build`, `flash`, `build and flash`, `rebuild`, `clean` (see .vscode tasks / workspace tasks).
- Debug configs live in `Project/DebugConfig/` and `JLinkSettings.ini`. Load the `.axf` from `Project/Objects/` when using the debugger.

-- Important file examples to reference (use concrete samples)
- Task example: `Apply/Task/Inc/task_motorsys.h` + `Apply/Task/Src/task_motorsys.c` ¡ª shows how tasks call driver APIs (`Task_MotorSys_Thruster_SpeedSet` ¡ú `Drv_PWM_HighLvTimeSet`).
- Driver example: `Driver/Src/drv_hal_pwm.c` ¡ª shows init, per-channel API, macro guards (`#ifdef DRV_HAL_PWM_ENABLE`) and error call sites.
- Build integration: `Project/STM32.uvprojx` and `.eide/eide.json` list include paths and source groups; `.vscode/c_cpp_properties.json` contains the same include directories used by tools.

-- Project-specific patterns (do not invent these)
- Drivers expose small, deterministic APIs and use short blocking delays (e.g. `Drv_Delay_Ms(...)`) in initialization flows¡ªbe conservative changing timing.
- PWM and servo patterns use "high level time (us)" constants (example names in `task_motorsys.c`: `STOP_PWM_HIGHTIME`, `ANGLE_90_PWM_HIGHTIME`) ¡ª rely on existing constants and do not re-scale without checking hardware wiring.
- Task coordination frequently uses direct API calls between tasks (see `task_handlemode.c` invoking `Task_MotorSys_...`). Respect ordering and possible delays between calls.

-- Integration & constraints an agent must know
- Hardware assumptions: target is STM32F1 series (macros like `STM32F103xE` appear in build), HAL drivers mixed with custom drivers.
- Avoid changes that require Keil pack updates or different toolchains unless user authorizes; prefer edits to C sources and headers.
- Many files are included in `.uvprojx` and build logs under `Project/Objects/`; test compile locally using the `build` task before proposing large refactors.

-- What to do when making edits (checklist for pull requests)
1. Keep header/source parity under `Apply/Task/Inc` & `Apply/Task/Src` or `Driver/Inc` & `Driver/Src`.
2. Update `drv_hal_conf.h` to enable any new driver and guard with a macro (`DRV_HAL_*_ENABLE`).
3. Run the `build` task (VS Code / EIDE) and include the resulting small compile log excerpt in the PR if you touched low-level drivers.
4. If changing timing or PWM math, reference `Driver/Src/drv_hal_pwm.c` and `Apply/Task/Src/task_motorsys.c` examples; note hardware-dependent constants.

-- If something is not discoverable
- Ask the repo owner for the Keil/MDK toolchain version (Keil v5 pack path is referenced in build logs) and the hardware wiring for PWM channels.

---
If any section is unclear or you'd like me to expand the debug/run commands or add a short onboarding checklist for humans, tell me which area to expand.
```