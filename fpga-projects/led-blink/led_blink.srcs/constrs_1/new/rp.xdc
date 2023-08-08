set_property IOSTANDARD DIFF_HSTL_I_18 [get_ports adc_clk_p[0]]
set_property IOSTANDARD DIFF_HSTL_I_18 [get_ports adc_clk_n[0]]
set_property PACKAGE_PIN U18 [get_ports adc_clk_p[0]]
set_property PACKAGE_PIN U19 [get_ports adc_clk_n[0]]

set_property IOSTANDARD DIFF_HSTL_I_18 [get_ports daisy_p[*]]
set_property IOSTANDARD DIFF_HSTL_I_18 [get_ports daisy_n[*]]

set_property PACKAGE_PIN P14 [get_ports {daisy_p[0]}]
set_property PACKAGE_PIN R14 [get_ports {daisy_n[0]}]

set_property PACKAGE_PIN N18 [get_ports {daisy_p[1]}]
set_property PACKAGE_PIN P19 [get_ports {daisy_n[1]}]

set_property IOSTANDARD LVCMOS33 [get_ports {led[*]}]
set_property SLEW SLOW [get_ports {led[*]}]
set_property DRIVE 8 [get_ports {led[*]}]

set_property PACKAGE_PIN F16 [get_ports {led[0]}]
set_property PACKAGE_PIN F17 [get_ports {led[1]}]
set_property PACKAGE_PIN G15 [get_ports {led[2]}]
set_property PACKAGE_PIN H15 [get_ports {led[3]}]
set_property PACKAGE_PIN K14 [get_ports {led[4]}]