# Netlist reference

One statement per line. `#` starts a comment. Lengths and wavelengths are in micrometres.

| Statement | Meaning | Default |
|---|---|---|
| `title <text>` | name shown in reports | empty |
| `medium lambda0=.. neff=.. ng=.. loss_db_cm=..` | waveguide properties used by every component that propagates light | 1.55, 2.4, 4.2, 0 |
| `sweep <from> <to> <points>` | wavelength range | 1.5 to 1.6, 1001 points |
| `feature <dB>` | smallest prominence that counts as a resonance | 3 |
| `comp <name> <kind> key=value ...` | a component | |
| `link <comp.port> <comp.port>` | joins two ports | |
| `port <name> <comp.port>` | makes a port external | |
| `excite <port name>` | the driven port | the first external port |
| `expect <kind> <args>` | an expectation, see below | |

Ports are numbered from 1. A port may appear in one link or one `port` statement, not more.

## Expectations

| Kind | Arguments | Passes when |
|---|---|---|
| `lossless` | `[tol]` | the external matrix is unitary within tol (1e-9) at every wavelength |
| `passive` | | no single input gives more than unit total output |
| `reciprocal` | `[tol]` | the external matrix is symmetric within tol |
| `fsr` | `port dips|peaks nm reltol` | the mean spacing of resonances matches |
| `fwhm` | `port dips|peaks nm reltol` | the width of the resonance nearest the centre matches |
| `count` | `port dips|peaks n` | exactly n resonances are found |
| `center` | `port dips|peaks um tol_nm` | the resonance nearest a wavelength is within tol |
| `level` | `port um dB tol_dB` | the transmission at a wavelength matches |
| `min`, `max` | `port dB tol_dB` | the extreme over the sweep matches |
| `below`, `above` | `port dB` | the whole sweep stays under, or over, a bound |
| `deeper` | `port dB` | the minimum is below a bound |
| `extinction` | `port dB tol_dB` | maximum minus minimum matches |
| `uniform` | `tol_dB` | all ports except the driven one agree at the centre wavelength |
| `delay` | `port um ps reltol` | the group delay at a wavelength matches |
| `phase_step` | `um degrees tol_degrees` | consecutive ports, driven port excluded, differ by this phase |

A malformed expectation is reported as a failed check with the line number; it does not stop the run.

## Command line

```
lightcircuit run <netlist>     metrics, checks and the spectrum
lightcircuit check <netlist>   metrics and checks; exit status 1 if a check fails
lightcircuit info <netlist>    structure only
```

Exit status 2 means the netlist could not be read or built; the reason is on standard error.
