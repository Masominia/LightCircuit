# Component reference

Amplitudes, not powers, unless stated. `i` is the imaginary unit.

| Kind | Ports | Parameters | Scattering |
|---|---|---|---|
| `waveguide` | 1, 2 | `length`; optional `phase`, `neff`, `ng`, `loss_db_cm` | 1 to 2: `exp(i beta L - alpha L + i phase)`; no reflection |
| `phase` | 1, 2 | `phi` (radians) | 1 to 2: `exp(i phi)` at every wavelength |
| `attenuator` | 1, 2 | `db` | 1 to 2: `10^(-db/20)` |
| `coupler` | 1, 2 on one side, 3, 4 on the other | `kappa` (power); optional `excess_db` | 1 to 3 and 2 to 4: `t = sqrt(1 - kappa)`; 1 to 4 and 2 to 3: `i sqrt(kappa)` |
| `splitter` | 1 stem, 2 and 3 arms | optional `ratio` (0.5), `excess_db` | 1 to 2: `sqrt(ratio)`, 1 to 3: `sqrt(1 - ratio)` |
| `reflector` | 1, 2 | `reflectivity` (power) | reflection `sqrt(R)` on both sides, transmission `i sqrt(1 - R)` |
| `mirror` | 1 | optional `reflectivity` (1), `phase` | reflection `sqrt(R) exp(i phase)` |
| `terminator` | 1 | | absorbs everything |
| `bragg` | 1, 2 | `length`, `kappa` (per micrometre), `bragg_lambda` | coupled-mode theory, see `methodology.md` |

All components are reciprocal. Coupler, reflector, lossless waveguide, phase shifter and Bragg grating are lossless.

## Notes

- **Coupler orientation.** Port 1 faces port 3 and port 2 faces port 4. A ring coupled to a bus uses ports 1 and 3 for the bus and closes the ring from port 4 back to port 2.
- **Add-drop ring.** With the ring entering the second coupler at port 4, the drop port is port 1 of that coupler and the add port is port 3.
- **Y-branch.** A three-port cannot be lossless, reciprocal and matched at all ports. This one is matched at the stem: used as a combiner it passes the in-phase part of the two arms and loses the rest, which is what a single-mode Y-branch does.
- **Bragg grating.** Reflection is referred to the two ends of the grating. A cavity between two gratings therefore includes the grating phase.
