# LightCircuit report

69 circuits, 386 components, 288 checks: 288 PASS, 0 FAIL.

Every circuit is a netlist in `cases/`. Its expectations come from closed-form results stated in the comments at the top of the file.
Per-circuit results are in `reports/cases/`, spectra in `reports/figures/cases/`.

## Families

| family | cases | components | checks | passed |
|---|---|---|---|---|
| waveguides | 5 | 9 | 13 | 13 |
| cavities and mirrors | 10 | 24 | 43 | 43 |
| couplers | 5 | 6 | 21 | 21 |
| coupled rings | 6 | 75 | 24 | 24 |
| Mach-Zehnder | 11 | 51 | 44 | 44 |
| phased-array feeds | 5 | 83 | 17 | 17 |
| add-drop rings | 10 | 48 | 53 | 53 |
| all-pass rings | 10 | 23 | 28 | 28 |
| splitter trees | 7 | 67 | 33 | 33 |

## Whole spectra against closed forms

For these circuits the complete spectrum is compared, point by point, with a formula written separately in Python (`src/lightcircuit/analytic.py`).

| case | ports | points | largest power difference |
|---|---|---|---|
| bragg_strong | in, out | 8,001 | 1.15e-11 |
| bragg_weak | in, out | 8,001 | 1.15e-11 |
| fabry_perot_r30 | in, out | 16,001 | 1.16e-11 |
| fabry_perot_r90 | in, out | 16,001 | 1.78e-11 |
| michelson | in, out | 8,001 | 1.15e-11 |
| mzi_dl_100 | bar, cross | 8,001 | 1.15e-11 |
| mzi_unbalanced_couplers | bar, cross | 8,001 | 1.15e-11 |
| ring_adddrop_asymmetric | drop, through | 16,001 | 1.26e-10 |
| ring_adddrop_strong | drop, through | 16,001 | 5.87e-11 |
| ring_adddrop_symmetric | drop, through | 16,001 | 2.50e-10 |
| ring_allpass_lossless | through | 4,001 | 4.88e-15 |
| ring_allpass_r10 | through | 16,001 | 2.90e-10 |

## All circuits

| case | circuit | components | ports | points | checks | passed |
|---|---|---|---|---|---|---|
| attenuator_chain | Three attenuators in series | 3 | 2 | 101 | 2 | 2 |
| bragg_cavity | Cavity between two Bragg gratings | 3 | 2 | 40,001 | 4 | 4 |
| bragg_medium | Uniform Bragg grating, kappa L = 1 | 1 | 2 | 8,001 | 5 | 5 |
| bragg_strong | Uniform Bragg grating, kappa L = 3 | 1 | 2 | 8,001 | 5 | 5 |
| bragg_weak | Uniform Bragg grating, kappa L = 0.3 | 1 | 2 | 8,001 | 5 | 5 |
| coupler_10_90 | Directional coupler, 10% cross coupling | 1 | 4 | 21 | 5 | 5 |
| coupler_3db | Directional coupler, 50% cross coupling | 1 | 4 | 21 | 5 | 5 |
| coupler_90_10 | Directional coupler, 90% cross coupling | 1 | 4 | 21 | 5 | 5 |
| coupler_excess_loss | 3 dB coupler with 0.3 dB excess loss | 1 | 4 | 21 | 3 | 3 |
| coupler_pair_full_cross | Two 3 dB couplers back to back | 2 | 4 | 21 | 3 | 3 |
| crow_2_rings | Coupled-resonator filter, 2 rings | 7 | 4 | 8,001 | 4 | 4 |
| crow_3_rings | Coupled-resonator filter, 3 rings | 10 | 4 | 8,001 | 4 | 4 |
| crow_3_rings_lossy | Three coupled rings with loss | 10 | 4 | 8,001 | 4 | 4 |
| crow_4_rings | Coupled-resonator filter, 4 rings | 13 | 4 | 8,001 | 4 | 4 |
| crow_5_rings | Coupled-resonator filter, 5 rings | 16 | 4 | 8,001 | 4 | 4 |
| crow_6_rings | Coupled-resonator filter, 6 rings | 19 | 4 | 8,001 | 4 | 4 |
| fabry_perot_r30 | Fabry-Perot cavity, mirror reflectivity 30% | 3 | 2 | 16,001 | 4 | 4 |
| fabry_perot_r60 | Fabry-Perot cavity, mirror reflectivity 60% | 3 | 2 | 16,001 | 5 | 5 |
| fabry_perot_r90 | Fabry-Perot cavity, mirror reflectivity 90% | 3 | 2 | 16,001 | 5 | 5 |
| lattice_two_stage | Two-stage lattice filter | 7 | 4 | 8,001 | 3 | 3 |
| michelson | Michelson interferometer, arm difference 50 um | 5 | 2 | 8,001 | 4 | 4 |
| mzi_balanced | Balanced Mach-Zehnder | 4 | 4 | 201 | 4 | 4 |
| mzi_dl_100 | Mach-Zehnder, arm difference 100 um | 4 | 4 | 8,001 | 5 | 5 |
| mzi_dl_200 | Mach-Zehnder, arm difference 200 um | 4 | 4 | 8,001 | 5 | 5 |
| mzi_dl_400 | Mach-Zehnder, arm difference 400 um | 4 | 4 | 8,001 | 5 | 5 |
| mzi_dl_50 | Mach-Zehnder, arm difference 50 um | 4 | 4 | 8,001 | 5 | 5 |
| mzi_lossy_arm | Mach-Zehnder with 3 dB of loss in one arm | 5 | 4 | 8,001 | 4 | 4 |
| mzi_switch_bar | Mach-Zehnder switch, phase 1.000 pi | 5 | 4 | 21 | 3 | 3 |
| mzi_switch_quadrature | Mach-Zehnder switch, phase 0.500 pi | 5 | 4 | 21 | 3 | 3 |
| mzi_switch_third | Mach-Zehnder switch, phase 0.333 pi | 5 | 4 | 21 | 3 | 3 |
| mzi_unbalanced_couplers | Mach-Zehnder with 40/60 couplers | 4 | 4 | 8,001 | 4 | 4 |
| opa_feed_1x16_equal | Equal-path feed for a 16-element array | 31 | 17 | 61 | 5 | 5 |
| opa_feed_1x4_heaters | Four-element feed with phase shifters | 7 | 5 | 21 | 3 | 3 |
| opa_feed_1x8_delay_center | Delay-line feed for an 8-element array, read at 1.55 um | 15 | 9 | 3,001 | 3 | 3 |
| opa_feed_1x8_delay_steered | Delay-line feed for an 8-element array, read at 1.56 um | 15 | 9 | 3,001 | 3 | 3 |
| opa_feed_1x8_lossy_delay | Delay-line feed with propagation loss | 15 | 9 | 201 | 3 | 3 |
| ring_adddrop_asymmetric | Add-drop ring, radius 10 um, coupling 0.2 / 0.05 | 4 | 4 | 16,001 | 7 | 7 |
| ring_adddrop_critical | Add-drop ring at critical coupling | 4 | 4 | 16,001 | 2 | 2 |
| ring_adddrop_lossless | Add-drop ring without loss | 4 | 4 | 16,001 | 4 | 4 |
| ring_adddrop_r25 | Add-drop ring, radius 25 um, coupling 0.1 / 0.1 | 4 | 4 | 16,001 | 7 | 7 |
| ring_adddrop_r5 | Add-drop ring, radius 5 um, coupling 0.1 / 0.1 | 4 | 4 | 16,001 | 6 | 6 |
| ring_adddrop_strong | Add-drop ring, radius 10 um, coupling 0.4 / 0.4 | 4 | 4 | 16,001 | 7 | 7 |
| ring_adddrop_symmetric | Add-drop ring, radius 10 um, coupling 0.1 / 0.1 | 4 | 4 | 16,001 | 7 | 7 |
| ring_adddrop_weak | Add-drop ring, radius 10 um, coupling 0.02 / 0.02 | 4 | 4 | 16,001 | 6 | 6 |
| ring_allpass_critical | All-pass ring at critical coupling | 2 | 2 | 16,001 | 3 | 3 |
| ring_allpass_linewidth | All-pass ring: linewidth and quality factor | 2 | 2 | 16,001 | 2 | 2 |
| ring_allpass_lossless | All-pass ring without loss | 2 | 2 | 4,001 | 2 | 2 |
| ring_allpass_overcoupled | All-pass ring, over-coupled | 2 | 2 | 16,001 | 3 | 3 |
| ring_allpass_r10 | All-pass ring, radius 10 um | 2 | 2 | 16,001 | 3 | 3 |
| ring_allpass_r20 | All-pass ring, radius 20 um | 2 | 2 | 16,001 | 3 | 3 |
| ring_allpass_r5 | All-pass ring, radius 5 um | 2 | 2 | 16,001 | 3 | 3 |
| ring_allpass_r50 | All-pass ring, radius 50 um | 2 | 2 | 16,001 | 3 | 3 |
| ring_allpass_undercoupled | All-pass ring, under-coupled | 2 | 2 | 16,001 | 3 | 3 |
| ring_loaded_mzi | Mach-Zehnder with a ring on one arm | 7 | 4 | 16,001 | 4 | 4 |
| sagnac_loop_20 | Sagnac loop mirror, coupling 20% | 2 | 2 | 201 | 3 | 3 |
| sagnac_loop_3db | Sagnac loop mirror, coupling 50% | 2 | 2 | 201 | 3 | 3 |
| tree_1x16 | 1x16 splitter tree | 15 | 17 | 21 | 5 | 5 |
| tree_1x2 | 1x2 splitter tree | 1 | 3 | 21 | 5 | 5 |
| tree_1x32 | 1x32 splitter tree | 31 | 33 | 21 | 5 | 5 |
| tree_1x4 | 1x4 splitter tree | 3 | 5 | 21 | 5 | 5 |
| tree_1x4_tapered | 1x4 tree with uneven first split | 3 | 5 | 21 | 5 | 5 |
| tree_1x8 | 1x8 splitter tree | 7 | 9 | 21 | 5 | 5 |
| tree_1x8_excess_loss | 1x8 tree, 0.2 dB excess loss per splitter | 7 | 9 | 21 | 3 | 3 |
| two_rings_one_bus | Two all-pass rings on one bus | 5 | 2 | 16,001 | 3 | 3 |
| vernier_cascade | Vernier filter: two rings of 10 and 11 um in cascade | 9 | 6 | 40,001 | 3 | 3 |
| wg_lossy_1cm | Straight waveguide, 1 cm at 2 dB/cm | 1 | 2 | 4,001 | 3 | 3 |
| wg_spiral_5cm | Spiral delay line, 5 cm at 1.5 dB/cm | 1 | 2 | 2,001 | 2 | 2 |
| wg_straight_delay | Straight waveguide, 1 mm, lossless | 1 | 2 | 4,001 | 4 | 4 |
| wg_three_sections | Three sections with different loss | 3 | 2 | 4,001 | 2 | 2 |
