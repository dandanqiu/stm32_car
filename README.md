# 平衡小车

目标芯片：STM32F103C8；编译器：ARMCC 5（EIDE 配置为 AC5）。

## 工程文件

- EIDE：打开 `平衡小车.code-workspace`，使用 `.eide/eide.yml`。
- Keil：打开 `平衡小车.uvprojx`。
- `user`、`my_lib`、`startup`、`std_periph_driver` 和 `.cmsis/include` 保留在仓库中。

## 换电脑后恢复依赖

安装并配置 ARMCC 5 和所用 IDE。EIDE 工程引用 Keil 的 `STM32F1xx_DFP` **2.3.0** 芯片包，需要通过 EIDE 的芯片包管理安装对应版本，确保工程内路径为 `.pack/Keil/STM32F1xx_DFP.2.3.0`。使用 Keil 时也需要安装对应芯片包。

`.pack`、其他芯片的 CMSIS 示例、编译输出、日志、个人界面状态和可选字体转换工具不纳入 Git；本地已有文件可以继续使用。OLED 字库头文件保留。
