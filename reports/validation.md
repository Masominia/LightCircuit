# Validation checks

| area | check | status | detail |
|---|---|---|---|
| waveguides | attenuator_chain: level out 1.55 -6 1e-9 | PASS | -6.0000 dB, expected -6.0000, off by -8.88e-16 |
| waveguides | attenuator_chain: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| cavities and mirrors | bragg_cavity: lossless 1e-7 | PASS | defect 1.78e-15, tolerance 1.0e-07 |
| cavities and mirrors | bragg_cavity: reciprocal 1e-9 | PASS | defect 5.03e-16, tolerance 1.0e-09 |
| cavities and mirrors | bragg_cavity: max out 0 0.05 | PASS | -0.0000 dB, expected 0.0000, off by -7.28e-14 |
| cavities and mirrors | bragg_cavity: deeper out -15 | PASS | minimum -18.379 dB, required below -15.000 |
| cavities and mirrors | bragg_medium: lossless 1e-8 | PASS | defect 8.88e-16, tolerance 1.0e-08 |
| cavities and mirrors | bragg_medium: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| cavities and mirrors | bragg_medium: max in -2.3655 0.01 | PASS | -2.3655 dB, expected -2.3655, off by -2.79e-05 |
| cavities and mirrors | bragg_medium: center in peaks 1.55 0.02 | PASS | 1.550000 um, expected 1.550000, off by 0.0000 nm |
| cavities and mirrors | bragg_medium: level out 1.55 -3.7678 0.01 | PASS | -3.7678 dB, expected -3.7678, off by 2.76e-05 |
| cavities and mirrors | bragg_strong: lossless 1e-8 | PASS | defect 1.11e-15, tolerance 1.0e-08 |
| cavities and mirrors | bragg_strong: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| cavities and mirrors | bragg_strong: max in -0.0431 0.01 | PASS | -0.0431 dB, expected -0.0431, off by 3.96e-05 |
| cavities and mirrors | bragg_strong: center in peaks 1.55 0.02 | PASS | 1.550000 um, expected 1.550000, off by 0.0000 nm |
| cavities and mirrors | bragg_strong: level out 1.55 -20.0586 0.01 | PASS | -20.0586 dB, expected -20.0586, off by 2.75e-05 |
| closed form | bragg_strong: whole spectrum against the formula | PASS | largest difference 1.2e-11 in linear power over 8001 points |
| cavities and mirrors | bragg_weak: lossless 1e-8 | PASS | defect 8.88e-16, tolerance 1.0e-08 |
| cavities and mirrors | bragg_weak: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| cavities and mirrors | bragg_weak: max in -10.7128 0.01 | PASS | -10.7128 dB, expected -10.7128, off by -1.42e-05 |
| cavities and mirrors | bragg_weak: center in peaks 1.55 0.02 | PASS | 1.550000 um, expected 1.550000, off by 0.0000 nm |
| cavities and mirrors | bragg_weak: level out 1.55 -0.3851 0.01 | PASS | -0.3851 dB, expected -0.3851, off by -3.90e-05 |
| closed form | bragg_weak: whole spectrum against the formula | PASS | largest difference 1.2e-11 in linear power over 8001 points |
| couplers | coupler_10_90: lossless | PASS | defect 1.11e-16, tolerance 1.0e-09 |
| couplers | coupler_10_90: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| couplers | coupler_10_90: level cross 1.55 -10.00000000 1e-6 | PASS | -10.0000 dB, expected -10.0000, off by 0.00e+00 |
| couplers | coupler_10_90: level bar 1.55 -0.45757491 1e-6 | PASS | -0.4576 dB, expected -0.4576, off by 4.39e-09 |
| couplers | coupler_10_90: below isolated -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| couplers | coupler_3db: lossless | PASS | defect 2.22e-16, tolerance 1.0e-09 |
| couplers | coupler_3db: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| couplers | coupler_3db: level cross 1.55 -3.01029996 1e-6 | PASS | -3.0103 dB, expected -3.0103, off by 3.36e-09 |
| couplers | coupler_3db: level bar 1.55 -3.01029996 1e-6 | PASS | -3.0103 dB, expected -3.0103, off by 3.36e-09 |
| couplers | coupler_3db: below isolated -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| couplers | coupler_90_10: lossless | PASS | defect 1.11e-16, tolerance 1.0e-09 |
| couplers | coupler_90_10: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| couplers | coupler_90_10: level cross 1.55 -0.45757491 1e-6 | PASS | -0.4576 dB, expected -0.4576, off by 4.39e-09 |
| couplers | coupler_90_10: level bar 1.55 -10.00000000 1e-6 | PASS | -10.0000 dB, expected -10.0000, off by -1.78e-15 |
| couplers | coupler_90_10: below isolated -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| couplers | coupler_excess_loss: passive | PASS | largest output power 0.933254301 |
| couplers | coupler_excess_loss: level bar 1.55 -3.31029996 1e-6 | PASS | -3.3103 dB, expected -3.3103, off by 3.36e-09 |
| couplers | coupler_excess_loss: level cross 1.55 -3.31029996 1e-6 | PASS | -3.3103 dB, expected -3.3103, off by 3.36e-09 |
| couplers | coupler_pair_full_cross: lossless | PASS | defect 4.44e-16, tolerance 1.0e-09 |
| couplers | coupler_pair_full_cross: level cross 1.55 0 1e-9 | PASS | 0.0000 dB, expected 0.0000, off by 1.93e-15 |
| couplers | coupler_pair_full_cross: below bar -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| coupled rings | crow_2_rings: lossless 1e-7 | PASS | defect 4.00e-15, tolerance 1.0e-07 |
| coupled rings | crow_2_rings: reciprocal 1e-7 | PASS | defect 9.31e-16, tolerance 1.0e-07 |
| coupled rings | crow_2_rings: max drop 0 0.05 | PASS | -0.0016 dB, expected 0.0000, off by -1.56e-03 |
| coupled rings | crow_2_rings: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| coupled rings | crow_3_rings: lossless 1e-7 | PASS | defect 7.33e-15, tolerance 1.0e-07 |
| coupled rings | crow_3_rings: reciprocal 1e-7 | PASS | defect 2.74e-15, tolerance 1.0e-07 |
| coupled rings | crow_3_rings: max drop 0 0.05 | PASS | -0.0000 dB, expected 0.0000, off by -5.34e-07 |
| coupled rings | crow_3_rings: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| coupled rings | crow_3_rings_lossy: passive | PASS | largest output power 0.999611120 |
| coupled rings | crow_3_rings_lossy: reciprocal 1e-7 | PASS | defect 1.95e-15, tolerance 1.0e-07 |
| coupled rings | crow_3_rings_lossy: below drop -0.05 | PASS | maximum -0.1621 dB, bound -0.0500 |
| coupled rings | crow_3_rings_lossy: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| coupled rings | crow_4_rings: lossless 1e-7 | PASS | defect 1.13e-14, tolerance 1.0e-07 |
| coupled rings | crow_4_rings: reciprocal 1e-7 | PASS | defect 3.38e-15, tolerance 1.0e-07 |
| coupled rings | crow_4_rings: max drop 0 0.05 | PASS | -0.0000 dB, expected 0.0000, off by -3.03e-05 |
| coupled rings | crow_4_rings: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| coupled rings | crow_5_rings: lossless 1e-7 | PASS | defect 2.15e-14, tolerance 1.0e-07 |
| coupled rings | crow_5_rings: reciprocal 1e-7 | PASS | defect 3.99e-15, tolerance 1.0e-07 |
| coupled rings | crow_5_rings: max drop 0 0.05 | PASS | -0.0000 dB, expected 0.0000, off by -1.91e-06 |
| coupled rings | crow_5_rings: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| coupled rings | crow_6_rings: lossless 1e-7 | PASS | defect 2.63e-14, tolerance 1.0e-07 |
| coupled rings | crow_6_rings: reciprocal 1e-7 | PASS | defect 6.12e-15, tolerance 1.0e-07 |
| coupled rings | crow_6_rings: max drop 0 0.05 | PASS | -0.0000 dB, expected 0.0000, off by -4.90e-06 |
| coupled rings | crow_6_rings: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| cavities and mirrors | fabry_perot_r30: lossless 1e-8 | PASS | defect 9.99e-16, tolerance 1.0e-08 |
| cavities and mirrors | fabry_perot_r30: fsr out peaks 1.43006 0.005 | PASS | 1.42973 nm, expected 1.43006, relative error -2.32e-04 |
| cavities and mirrors | fabry_perot_r30: max out 0 0.01 | PASS | -0.0000 dB, expected 0.0000, off by -1.13e-08 |
| cavities and mirrors | fabry_perot_r30: min out -5.3769 0.05 | PASS | -5.3769 dB, expected -5.3769, off by -6.19e-06 |
| closed form | fabry_perot_r30: whole spectrum against the formula | PASS | largest difference 1.2e-11 in linear power over 16001 points |
| cavities and mirrors | fabry_perot_r60: lossless 1e-8 | PASS | defect 1.78e-15, tolerance 1.0e-08 |
| cavities and mirrors | fabry_perot_r60: fsr out peaks 1.43006 0.005 | PASS | 1.43101 nm, expected 1.43006, relative error 6.62e-04 |
| cavities and mirrors | fabry_perot_r60: max out 0 0.01 | PASS | -0.0000 dB, expected 0.0000, off by -6.92e-08 |
| cavities and mirrors | fabry_perot_r60: min out -12.0412 0.05 | PASS | -12.0412 dB, expected -12.0412, off by 2.48e-07 |
| cavities and mirrors | fabry_perot_r60: fwhm out peaks 0.223030 0.01 | PASS | 0.22318 nm, expected 0.22303, relative error 6.57e-04 |
| cavities and mirrors | fabry_perot_r90: lossless 1e-8 | PASS | defect 6.33e-15, tolerance 1.0e-08 |
| cavities and mirrors | fabry_perot_r90: fsr out peaks 1.43006 0.005 | PASS | 1.42968 nm, expected 1.43006, relative error -2.66e-04 |
| cavities and mirrors | fabry_perot_r90: max out 0 0.01 | PASS | -0.0000 dB, expected 0.0000, off by -1.87e-05 |
| cavities and mirrors | fabry_perot_r90: min out -25.5751 0.05 | PASS | -25.5751 dB, expected -25.5751, off by 2.86e-05 |
| cavities and mirrors | fabry_perot_r90: fwhm out peaks 0.047872 0.01 | PASS | 0.04791 nm, expected 0.04787, relative error 7.14e-04 |
| closed form | fabry_perot_r90: whole spectrum against the formula | PASS | largest difference 1.8e-11 in linear power over 16001 points |
| Mach-Zehnder | lattice_two_stage: lossless | PASS | defect 8.88e-16, tolerance 1.0e-09 |
| Mach-Zehnder | lattice_two_stage: reciprocal | PASS | defect 4.74e-16, tolerance 1.0e-09 |
| Mach-Zehnder | lattice_two_stage: fsr bar dips 5.72024 0.01 | PASS | 5.71841 nm, expected 5.72024, relative error -3.19e-04 |
| cavities and mirrors | michelson: lossless | PASS | defect 8.88e-16, tolerance 1.0e-09 |
| cavities and mirrors | michelson: fsr out dips 5.72024 0.005 | PASS | 5.71909 nm, expected 5.72024, relative error -2.01e-04 |
| cavities and mirrors | michelson: fsr in dips 5.72024 0.005 | PASS | 5.71850 nm, expected 5.72024, relative error -3.05e-04 |
| cavities and mirrors | michelson: max out 0 1e-3 | PASS | -0.0000 dB, expected 0.0000, off by -2.88e-10 |
| closed form | michelson: whole spectrum against the formula | PASS | largest difference 1.1e-11 in linear power over 8001 points |
| Mach-Zehnder | mzi_balanced: lossless | PASS | defect 6.66e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_balanced: level cross 1.55 0 1e-9 | PASS | 0.0000 dB, expected 0.0000, off by 1.93e-15 |
| Mach-Zehnder | mzi_balanced: below bar -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| Mach-Zehnder | mzi_balanced: extinction cross 0 1e-9 | PASS | 0.000 dB, expected 0.000 |
| Mach-Zehnder | mzi_dl_100: lossless | PASS | defect 6.66e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_dl_100: fsr cross dips 5.72024 0.005 | PASS | 5.71909 nm, expected 5.72024, relative error -2.01e-04 |
| Mach-Zehnder | mzi_dl_100: fsr bar dips 5.72024 0.005 | PASS | 5.71850 nm, expected 5.72024, relative error -3.05e-04 |
| Mach-Zehnder | mzi_dl_100: max cross 0 1e-3 | PASS | -0.0000 dB, expected 0.0000, off by -2.88e-10 |
| Mach-Zehnder | mzi_dl_100: deeper cross -40 | PASS | minimum -81.244 dB, required below -40.000 |
| closed form | mzi_dl_100: whole spectrum against the formula | PASS | largest difference 1.1e-11 in linear power over 8001 points |
| Mach-Zehnder | mzi_dl_200: lossless | PASS | defect 6.66e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_dl_200: fsr cross dips 2.86012 0.005 | PASS | 2.85418 nm, expected 2.86012, relative error -2.08e-03 |
| Mach-Zehnder | mzi_dl_200: fsr bar dips 2.86012 0.005 | PASS | 2.85955 nm, expected 2.86012, relative error -2.01e-04 |
| Mach-Zehnder | mzi_dl_200: max cross 0 1e-3 | PASS | -0.0000 dB, expected 0.0000, off by -1.15e-09 |
| Mach-Zehnder | mzi_dl_200: deeper cross -40 | PASS | minimum -78.544 dB, required below -40.000 |
| Mach-Zehnder | mzi_dl_400: lossless | PASS | defect 8.88e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_dl_400: fsr cross dips 1.43006 0.005 | PASS | 1.42980 nm, expected 1.43006, relative error -1.84e-04 |
| Mach-Zehnder | mzi_dl_400: fsr bar dips 1.43006 0.005 | PASS | 1.42845 nm, expected 1.43006, relative error -1.12e-03 |
| Mach-Zehnder | mzi_dl_400: max cross 0 1e-3 | PASS | -0.0000 dB, expected 0.0000, off by -4.61e-09 |
| Mach-Zehnder | mzi_dl_400: deeper cross -40 | PASS | minimum -63.838 dB, required below -40.000 |
| Mach-Zehnder | mzi_dl_50: lossless | PASS | defect 6.66e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_dl_50: fsr cross dips 11.44048 0.005 | PASS | 11.43699 nm, expected 11.44048, relative error -3.05e-04 |
| Mach-Zehnder | mzi_dl_50: fsr bar dips 11.44048 0.005 | PASS | 11.43494 nm, expected 11.44048, relative error -4.84e-04 |
| Mach-Zehnder | mzi_dl_50: max cross 0 1e-3 | PASS | -0.0000 dB, expected 0.0000, off by -7.21e-11 |
| Mach-Zehnder | mzi_dl_50: deeper cross -40 | PASS | minimum -95.563 dB, required below -40.000 |
| Mach-Zehnder | mzi_lossy_arm: passive | PASS | largest output power 0.750593617 |
| Mach-Zehnder | mzi_lossy_arm: max cross -1.37112 1e-3 | PASS | -1.3711 dB, expected -1.3711, off by 1.70e-06 |
| Mach-Zehnder | mzi_lossy_arm: min cross -16.71133 1e-2 | PASS | -16.7113 dB, expected -16.7113, off by 7.57e-07 |
| Mach-Zehnder | mzi_lossy_arm: extinction bar 15.3402 0.02 | PASS | 15.340 dB, expected 15.340 |
| Mach-Zehnder | mzi_switch_bar: lossless | PASS | defect 4.44e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_switch_bar: level bar 1.55 0.00000000 1e-6 | PASS | 0.0000 dB, expected 0.0000, off by 9.64e-16 |
| Mach-Zehnder | mzi_switch_bar: below cross -200 | PASS | maximum -259.7044 dB, bound -200.0000 |
| Mach-Zehnder | mzi_switch_quadrature: lossless | PASS | defect 4.44e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_switch_quadrature: level bar 1.55 -3.01029996 1e-6 | PASS | -3.0103 dB, expected -3.0103, off by 3.36e-09 |
| Mach-Zehnder | mzi_switch_quadrature: level cross 1.55 -3.01029996 1e-6 | PASS | -3.0103 dB, expected -3.0103, off by 3.36e-09 |
| Mach-Zehnder | mzi_switch_third: lossless | PASS | defect 4.44e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_switch_third: level bar 1.55 -6.02059991 1e-6 | PASS | -6.0206 dB, expected -6.0206, off by -3.28e-09 |
| Mach-Zehnder | mzi_switch_third: level cross 1.55 -1.24938737 1e-6 | PASS | -1.2494 dB, expected -1.2494, off by 3.92e-09 |
| Mach-Zehnder | mzi_unbalanced_couplers: lossless | PASS | defect 4.44e-16, tolerance 1.0e-09 |
| Mach-Zehnder | mzi_unbalanced_couplers: extinction bar 13.9794 0.01 | PASS | 13.979 dB, expected 13.979 |
| Mach-Zehnder | mzi_unbalanced_couplers: deeper cross -40 | PASS | minimum -81.421 dB, required below -40.000 |
| Mach-Zehnder | mzi_unbalanced_couplers: max cross -0.17729 1e-3 | PASS | -0.1773 dB, expected -0.1773, off by 2.33e-06 |
| closed form | mzi_unbalanced_couplers: whole spectrum against the formula | PASS | largest difference 1.2e-11 in linear power over 8001 points |
| phased-array feeds | opa_feed_1x16_equal: passive | PASS | largest output power 1.000000000 |
| phased-array feeds | opa_feed_1x16_equal: uniform 1e-9 | PASS | outputs between -12.0412 and -12.0412 dB |
| phased-array feeds | opa_feed_1x16_equal: phase_step 1.55 0 1e-6 | PASS | largest deviation 0.0000 degrees from a step of 0.000 over 15 steps |
| phased-array feeds | opa_feed_1x16_equal: phase_step 1.58 0 1e-6 | PASS | largest deviation 0.0000 degrees from a step of 0.000 over 15 steps |
| phased-array feeds | opa_feed_1x16_equal: level out9 1.55 -12.04119983 1e-6 | PASS | -12.0412 dB, expected -12.0412, off by 3.44e-09 |
| phased-array feeds | opa_feed_1x4_heaters: uniform 1e-9 | PASS | outputs between -6.0206 and -6.0206 dB |
| phased-array feeds | opa_feed_1x4_heaters: phase_step 1.55 40 1e-6 | PASS | largest deviation 0.0000 degrees from a step of 40.000 over 3 steps |
| phased-array feeds | opa_feed_1x4_heaters: phase_step 1.52 40 1e-6 | PASS | largest deviation 0.0000 degrees from a step of 40.000 over 3 steps |
| phased-array feeds | opa_feed_1x8_delay_center: passive | PASS | largest output power 1.000000000 |
| phased-array feeds | opa_feed_1x8_delay_center: uniform 1e-9 | PASS | outputs between -9.0309 and -9.0309 dB |
| phased-array feeds | opa_feed_1x8_delay_center: phase_step 1.55 -11.6129 0.02 | PASS | largest deviation 0.0000 degrees from a step of -11.613 over 7 steps |
| phased-array feeds | opa_feed_1x8_delay_steered: passive | PASS | largest output power 1.000000000 |
| phased-array feeds | opa_feed_1x8_delay_steered: uniform 1e-9 | PASS | outputs between -9.0309 and -9.0309 dB |
| phased-array feeds | opa_feed_1x8_delay_steered: phase_step 1.56 -136.6749 0.02 | PASS | largest deviation 0.0000 degrees from a step of -136.675 over 7 steps |
| phased-array feeds | opa_feed_1x8_lossy_delay: passive | PASS | largest output power 0.988330450 |
| phased-array feeds | opa_feed_1x8_lossy_delay: level out1 1.55 -9.06089987 1e-6 | PASS | -9.0609 dB, expected -9.0609, off by 8.06e-11 |
| phased-array feeds | opa_feed_1x8_lossy_delay: level out8 1.55 -9.10289987 1e-6 | PASS | -9.1029 dB, expected -9.1029, off by 8.06e-11 |
| add-drop rings | ring_adddrop_asymmetric: passive | PASS | largest output power 0.999962836 |
| add-drop rings | ring_adddrop_asymmetric: reciprocal | PASS | defect 4.45e-16, tolerance 1.0e-09 |
| add-drop rings | ring_adddrop_asymmetric: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| add-drop rings | ring_adddrop_asymmetric: max drop -2.2504 0.03 | PASS | -2.2504 dB, expected -2.2504, off by 2.18e-05 |
| add-drop rings | ring_adddrop_asymmetric: min through -4.3088 0.1 | PASS | -4.3088 dB, expected -4.3088, off by -5.85e-06 |
| add-drop rings | ring_adddrop_asymmetric: fwhm drop peaks 0.400557 0.01 | PASS | 0.40193 nm, expected 0.40056, relative error 3.42e-03 |
| add-drop rings | ring_adddrop_asymmetric: fsr drop peaks 9.10404 0.005 | PASS | 9.08212 nm, expected 9.10404, relative error -2.41e-03 |
| closed form | ring_adddrop_asymmetric: whole spectrum against the formula | PASS | largest difference 1.3e-10 in linear power over 16001 points |
| add-drop rings | ring_adddrop_critical: passive | PASS | largest output power 0.999925810 |
| add-drop rings | ring_adddrop_critical: deeper through -30 | PASS | minimum -52.852 dB, required below -30.000 |
| add-drop rings | ring_adddrop_lossless: lossless 1e-8 | PASS | defect 6.11e-15, tolerance 1.0e-08 |
| add-drop rings | ring_adddrop_lossless: max drop 0 0.01 | PASS | -0.0000 dB, expected 0.0000, off by -7.07e-06 |
| add-drop rings | ring_adddrop_lossless: deeper through -40 | PASS | minimum -57.881 dB, required below -40.000 |
| add-drop rings | ring_adddrop_lossless: fsr drop peaks 9.10404 0.005 | PASS | 9.08212 nm, expected 9.10404, relative error -2.41e-03 |
| add-drop rings | ring_adddrop_r25: passive | PASS | largest output power 0.999809656 |
| add-drop rings | ring_adddrop_r25: reciprocal | PASS | defect 3.51e-16, tolerance 1.0e-09 |
| add-drop rings | ring_adddrop_r25: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| add-drop rings | ring_adddrop_r25: max drop -0.2935 0.03 | PASS | -0.2935 dB, expected -0.2935, off by 4.76e-05 |
| add-drop rings | ring_adddrop_r25: min through -29.5843 0.1 | PASS | -29.5842 dB, expected -29.5843, off by 1.32e-04 |
| add-drop rings | ring_adddrop_r25: fwhm drop peaks 0.126073 0.01 | PASS | 0.12620 nm, expected 0.12607, relative error 1.04e-03 |
| add-drop rings | ring_adddrop_r25: fsr drop peaks 3.64162 0.005 | PASS | 3.64541 nm, expected 3.64162, relative error 1.04e-03 |
| add-drop rings | ring_adddrop_r5: passive | PASS | largest output power 0.999961928 |
| add-drop rings | ring_adddrop_r5: reciprocal | PASS | defect 3.72e-16, tolerance 1.0e-09 |
| add-drop rings | ring_adddrop_r5: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| add-drop rings | ring_adddrop_r5: max drop -0.0595 0.03 | PASS | -0.0595 dB, expected -0.0595, off by 1.16e-05 |
| add-drop rings | ring_adddrop_r5: min through -43.3298 0.1 | PASS | -43.2924 dB, expected -43.3298, off by 3.74e-02 |
| add-drop rings | ring_adddrop_r5: fwhm drop peaks 0.613692 0.01 | PASS | 0.60860 nm, expected 0.61369, relative error -8.30e-03 |
| add-drop rings | ring_adddrop_strong: passive | PASS | largest output power 0.999638376 |
| add-drop rings | ring_adddrop_strong: reciprocal | PASS | defect 3.33e-16, tolerance 1.0e-09 |
| add-drop rings | ring_adddrop_strong: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| add-drop rings | ring_adddrop_strong: max drop -0.0251 0.03 | PASS | -0.0251 dB, expected -0.0251, off by 9.88e-07 |
| add-drop rings | ring_adddrop_strong: min through -51.0769 0.1 | PASS | -51.0395 dB, expected -51.0769, off by 3.74e-02 |
| add-drop rings | ring_adddrop_strong: fwhm drop peaks 1.423549 0.01 | PASS | 1.42838 nm, expected 1.42355, relative error 3.39e-03 |
| add-drop rings | ring_adddrop_strong: fsr drop peaks 9.10404 0.005 | PASS | 9.08212 nm, expected 9.10404, relative error -2.41e-03 |
| closed form | ring_adddrop_strong: whole spectrum against the formula | PASS | largest difference 5.9e-11 in linear power over 16001 points |
| add-drop rings | ring_adddrop_symmetric: passive | PASS | largest output power 0.999923858 |
| add-drop rings | ring_adddrop_symmetric: reciprocal | PASS | defect 4.44e-16, tolerance 1.0e-09 |
| add-drop rings | ring_adddrop_symmetric: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| add-drop rings | ring_adddrop_symmetric: max drop -0.1186 0.03 | PASS | -0.1186 dB, expected -0.1186, off by 2.33e-05 |
| add-drop rings | ring_adddrop_symmetric: min through -37.3682 0.1 | PASS | -37.3308 dB, expected -37.3682, off by 3.74e-02 |
| add-drop rings | ring_adddrop_symmetric: fwhm drop peaks 0.308931 0.01 | PASS | 0.31000 nm, expected 0.30893, relative error 3.45e-03 |
| add-drop rings | ring_adddrop_symmetric: fsr drop peaks 9.10404 0.005 | PASS | 9.08212 nm, expected 9.10404, relative error -2.41e-03 |
| closed form | ring_adddrop_symmetric: whole spectrum against the formula | PASS | largest difference 2.5e-10 in linear power over 16001 points |
| add-drop rings | ring_adddrop_weak: passive | PASS | largest output power 0.999985386 |
| add-drop rings | ring_adddrop_weak: reciprocal | PASS | defect 3.33e-16, tolerance 1.0e-09 |
| add-drop rings | ring_adddrop_weak: below add -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| add-drop rings | ring_adddrop_weak: max drop -0.6008 0.03 | PASS | -0.6009 dB, expected -0.6008, off by -1.30e-04 |
| add-drop rings | ring_adddrop_weak: min through -23.5012 0.1 | PASS | -23.4664 dB, expected -23.5012, off by 3.48e-02 |
| add-drop rings | ring_adddrop_weak: fwhm drop peaks 0.062733 0.01 | PASS | 0.06295 nm, expected 0.06273, relative error 3.46e-03 |
| all-pass rings | ring_allpass_critical: passive | PASS | largest output power 0.999947674 |
| all-pass rings | ring_allpass_critical: deeper through -30 | PASS | minimum -38.730 dB, required below -30.000 |
| all-pass rings | ring_allpass_critical: fsr through dips 4.55202 0.005 | PASS | 4.55416 nm, expected 4.55202, relative error 4.70e-04 |
| all-pass rings | ring_allpass_linewidth: passive | PASS | largest output power 0.999944348 |
| all-pass rings | ring_allpass_linewidth: fwhm through dips 0.080600 0.01 | PASS | 0.08088 nm, expected 0.08060, relative error 3.43e-03 |
| all-pass rings | ring_allpass_lossless: lossless 1e-8 | PASS | defect 7.66e-15, tolerance 1.0e-08 |
| all-pass rings | ring_allpass_lossless: extinction through 0 1e-7 | PASS | 0.000 dB, expected 0.000 |
| closed form | ring_allpass_lossless: whole spectrum against the formula | PASS | largest difference 4.9e-15 in linear power over 4001 points |
| all-pass rings | ring_allpass_overcoupled: passive | PASS | largest output power 0.999674147 |
| all-pass rings | ring_allpass_overcoupled: min through -2.8135 0.05 | PASS | -2.8135 dB, expected -2.8135, off by -4.68e-06 |
| all-pass rings | ring_allpass_overcoupled: fsr through dips 4.55202 0.005 | PASS | 4.55414 nm, expected 4.55202, relative error 4.67e-04 |
| all-pass rings | ring_allpass_r10: passive | PASS | largest output power 0.999944348 |
| all-pass rings | ring_allpass_r10: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| all-pass rings | ring_allpass_r10: fsr through dips 9.10404 0.005 | PASS | 9.14284 nm, expected 9.10404, relative error 4.26e-03 |
| closed form | ring_allpass_r10: whole spectrum against the formula | PASS | largest difference 2.9e-10 in linear power over 16001 points |
| all-pass rings | ring_allpass_r20: passive | PASS | largest output power 0.999888699 |
| all-pass rings | ring_allpass_r20: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| all-pass rings | ring_allpass_r20: fsr through dips 4.55202 0.005 | PASS | 4.55840 nm, expected 4.55202, relative error 1.40e-03 |
| all-pass rings | ring_allpass_r5: passive | PASS | largest output power 0.999972174 |
| all-pass rings | ring_allpass_r5: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| all-pass rings | ring_allpass_r5: fsr through dips 18.20808 0.005 | PASS | 18.28568 nm, expected 18.20808, relative error 4.26e-03 |
| all-pass rings | ring_allpass_r50: passive | PASS | largest output power 0.999721773 |
| all-pass rings | ring_allpass_r50: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| all-pass rings | ring_allpass_r50: fsr through dips 1.82081 0.005 | PASS | 1.82025 nm, expected 1.82081, relative error -3.10e-04 |
| all-pass rings | ring_allpass_undercoupled: passive | PASS | largest output power 0.999982642 |
| all-pass rings | ring_allpass_undercoupled: min through -5.9893 0.05 | PASS | -5.9854 dB, expected -5.9893, off by 3.92e-03 |
| all-pass rings | ring_allpass_undercoupled: fsr through dips 4.55202 0.005 | PASS | 4.55415 nm, expected 4.55202, relative error 4.67e-04 |
| add-drop rings | ring_loaded_mzi: lossless 1e-8 | PASS | defect 4.14e-15, tolerance 1.0e-08 |
| add-drop rings | ring_loaded_mzi: reciprocal 1e-8 | PASS | defect 0.00e+00, tolerance 1.0e-08 |
| add-drop rings | ring_loaded_mzi: deeper bar -20 | PASS | minimum -119.152 dB, required below -20.000 |
| add-drop rings | ring_loaded_mzi: max cross 0 0.01 | PASS | -0.0000 dB, expected 0.0000, off by -5.28e-12 |
| cavities and mirrors | sagnac_loop_20: lossless | PASS | defect 4.44e-16, tolerance 1.0e-09 |
| cavities and mirrors | sagnac_loop_20: level in 1.55 -1.93820026 1e-6 | PASS | -1.9382 dB, expected -1.9382, off by -1.61e-10 |
| cavities and mirrors | sagnac_loop_20: level out 1.55 -4.43697499 1e-6 | PASS | -4.4370 dB, expected -4.4370, off by -2.33e-09 |
| cavities and mirrors | sagnac_loop_3db: lossless | PASS | defect 6.66e-16, tolerance 1.0e-09 |
| cavities and mirrors | sagnac_loop_3db: level in 1.55 0.00000000 1e-6 | PASS | 0.0000 dB, expected 0.0000, off by 1.93e-15 |
| cavities and mirrors | sagnac_loop_3db: below out -200 | PASS | maximum -300.0000 dB, bound -200.0000 |
| splitter trees | tree_1x16: passive | PASS | largest output power 1.000000000 |
| splitter trees | tree_1x16: uniform 1e-9 | PASS | outputs between -12.0412 and -12.0412 dB |
| splitter trees | tree_1x16: level out1 1.55 -12.04119983 1e-6 | PASS | -12.0412 dB, expected -12.0412, off by 3.44e-09 |
| splitter trees | tree_1x16: level out16 1.55 -12.04119983 1e-6 | PASS | -12.0412 dB, expected -12.0412, off by 3.44e-09 |
| splitter trees | tree_1x16: phase_step 1.55 0 1e-9 | PASS | largest deviation 0.0000 degrees from a step of 0.000 over 15 steps |
| splitter trees | tree_1x2: passive | PASS | largest output power 1.000000000 |
| splitter trees | tree_1x2: uniform 1e-9 | PASS | outputs between -3.0103 and -3.0103 dB |
| splitter trees | tree_1x2: level out1 1.55 -3.01029996 1e-6 | PASS | -3.0103 dB, expected -3.0103, off by 3.36e-09 |
| splitter trees | tree_1x2: level out2 1.55 -3.01029996 1e-6 | PASS | -3.0103 dB, expected -3.0103, off by 3.36e-09 |
| splitter trees | tree_1x2: phase_step 1.55 0 1e-9 | PASS | largest deviation 0.0000 degrees from a step of 0.000 over 1 steps |
| splitter trees | tree_1x32: passive | PASS | largest output power 1.000000000 |
| splitter trees | tree_1x32: uniform 1e-9 | PASS | outputs between -15.0515 and -15.0515 dB |
| splitter trees | tree_1x32: level out1 1.55 -15.05149978 1e-6 | PASS | -15.0515 dB, expected -15.0515, off by -3.20e-09 |
| splitter trees | tree_1x32: level out32 1.55 -15.05149978 1e-6 | PASS | -15.0515 dB, expected -15.0515, off by -3.20e-09 |
| splitter trees | tree_1x32: phase_step 1.55 0 1e-9 | PASS | largest deviation 0.0000 degrees from a step of 0.000 over 31 steps |
| splitter trees | tree_1x4: passive | PASS | largest output power 1.000000000 |
| splitter trees | tree_1x4: uniform 1e-9 | PASS | outputs between -6.0206 and -6.0206 dB |
| splitter trees | tree_1x4: level out1 1.55 -6.02059991 1e-6 | PASS | -6.0206 dB, expected -6.0206, off by -3.28e-09 |
| splitter trees | tree_1x4: level out4 1.55 -6.02059991 1e-6 | PASS | -6.0206 dB, expected -6.0206, off by -3.28e-09 |
| splitter trees | tree_1x4: phase_step 1.55 0 1e-9 | PASS | largest deviation 0.0000 degrees from a step of 0.000 over 3 steps |
| splitter trees | tree_1x4_tapered: level out1 1.55 -4.55931956 1e-6 | PASS | -4.5593 dB, expected -4.5593, off by 3.50e-09 |
| splitter trees | tree_1x4_tapered: level out2 1.55 -4.55931956 1e-6 | PASS | -4.5593 dB, expected -4.5593, off by 3.50e-09 |
| splitter trees | tree_1x4_tapered: level out3 1.55 -8.23908741 1e-6 | PASS | -8.2391 dB, expected -8.2391, off by 5.57e-10 |
| splitter trees | tree_1x4_tapered: level out4 1.55 -8.23908741 1e-6 | PASS | -8.2391 dB, expected -8.2391, off by 5.57e-10 |
| splitter trees | tree_1x4_tapered: passive | PASS | largest output power 1.000000000 |
| splitter trees | tree_1x8: passive | PASS | largest output power 1.000000000 |
| splitter trees | tree_1x8: uniform 1e-9 | PASS | outputs between -9.0309 and -9.0309 dB |
| splitter trees | tree_1x8: level out1 1.55 -9.03089987 1e-6 | PASS | -9.0309 dB, expected -9.0309, off by 8.06e-11 |
| splitter trees | tree_1x8: level out8 1.55 -9.03089987 1e-6 | PASS | -9.0309 dB, expected -9.0309, off by 8.06e-11 |
| splitter trees | tree_1x8: phase_step 1.55 0 1e-9 | PASS | largest deviation 0.0000 degrees from a step of 0.000 over 7 steps |
| splitter trees | tree_1x8_excess_loss: uniform 1e-9 | PASS | outputs between -9.6309 and -9.6309 dB |
| splitter trees | tree_1x8_excess_loss: level out3 1.55 -9.63089987 1e-6 | PASS | -9.6309 dB, expected -9.6309, off by 8.06e-11 |
| splitter trees | tree_1x8_excess_loss: passive | PASS | largest output power 0.870963590 |
| all-pass rings | two_rings_one_bus: passive | PASS | largest output power 0.995198246 |
| all-pass rings | two_rings_one_bus: reciprocal | PASS | defect 8.01e-16, tolerance 1.0e-09 |
| all-pass rings | two_rings_one_bus: deeper through -2 | PASS | minimum -2.990 dB, required below -2.000 |
| add-drop rings | vernier_cascade: lossless 1e-7 | PASS | defect 8.44e-15, tolerance 1.0e-07 |
| add-drop rings | vernier_cascade: below out 0.0001 | PASS | maximum -0.0017 dB, bound 0.0001 |
| add-drop rings | vernier_cascade: max out 0 0.3 | PASS | -0.0017 dB, expected 0.0000, off by -1.66e-03 |
| waveguides | wg_lossy_1cm: passive | PASS | largest output power 0.630957344 |
| waveguides | wg_lossy_1cm: level out 1.55 -2 1e-9 | PASS | -2.0000 dB, expected -2.0000, off by 2.22e-16 |
| waveguides | wg_lossy_1cm: extinction out 0 1e-9 | PASS | 0.000 dB, expected 0.000 |
| waveguides | wg_spiral_5cm: level out 1.55 -7.5 1e-9 | PASS | -7.5000 dB, expected -7.5000, off by 0.00e+00 |
| waveguides | wg_spiral_5cm: delay out 1.55 700.48460 1e-4 | PASS | 700.48460 ps, expected 700.48460, relative error -1.00e-09 |
| waveguides | wg_straight_delay: lossless | PASS | defect 2.22e-16, tolerance 1.0e-09 |
| waveguides | wg_straight_delay: reciprocal | PASS | defect 0.00e+00, tolerance 1.0e-09 |
| waveguides | wg_straight_delay: level out 1.55 0 1e-9 | PASS | 0.0000 dB, expected 0.0000, off by 0.00e+00 |
| waveguides | wg_straight_delay: delay out 1.55 14.009692 1e-5 | PASS | 14.00969 ps, expected 14.00969, relative error -8.28e-11 |
| waveguides | wg_three_sections: level out 1.55 -2 1e-9 | PASS | -2.0000 dB, expected -2.0000, off by -8.88e-16 |
| waveguides | wg_three_sections: passive | PASS | largest output power 0.630957344 |
