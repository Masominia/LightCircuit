# Methods

## Scattering description

Every component with n ports is an n by n complex matrix S: `b = S a`, where a holds the amplitudes entering the ports and b those leaving. Power is |amplitude|^2. A lossless component has a unitary S, a reciprocal one a symmetric S.

Time dependence is such that a waveguide of length L multiplies the amplitude by `exp(i beta L - alpha L)`, with `beta = 2 pi neff(lambda) / lambda`.

## Solving a circuit

All component ports are numbered globally and the component matrices are placed on the diagonal of one large matrix S. A link between two ports says that what leaves one enters the other: `a = P b + a_ext`, where P exchanges linked ports and `a_ext` is the wave injected at an external port. Eliminating a gives

`(I - S P) b = S a_ext`

One LU factorisation per wavelength serves all external ports. The result is the scattering matrix between the external ports, with every internal reflection and feedback loop included exactly. No signal-flow ordering is needed, so rings inside interferometers inside cavities need no special treatment.

Ports that are neither linked nor external receive nothing and their outgoing wave is discarded: they absorb.

## Sweep diagnostics

At every wavelength the full external matrix is computed, and three numbers are kept over the sweep: the largest departure of `S^H S` from the identity, the largest asymmetry, and the largest total output power for any single input. They drive the `lossless`, `reciprocal` and `passive` expectations.

## Resonances

A dip or peak is a local extremum of the spectrum in decibels whose prominence is at least the `feature` threshold (3 dB unless the netlist says otherwise). Prominence is the height above the higher of the two lowest points reached on either side before a more extreme sample. The position is refined with a parabola through three samples.

- Spacing: last position minus first, over the number of intervals.
- Width: full width at the level halfway, in linear power, between the extremum and the opposite extreme found between its neighbours, with linear interpolation at the two crossings.
- Q: wavelength over width.

For an Airy line with round-trip coefficient rho the width defined this way is `FSR (2 / pi) asin(1 / sqrt(F + 2))` with `F = 4 rho / (1 - rho)^2`, which the library uses as the expected value. For rho near one it tends to the usual `FSR (1 - rho) / (pi sqrt(rho))`.

## Group delay

The phase is unwrapped along the sweep and differentiated: `tau = -(lambda^2 / (2 pi c)) dphi/dlambda`.

## Bragg grating

Coupled-mode theory for a uniform grating with coupling kappa and detuning `delta = beta - beta_B`:

`r = -i kappa sinh(sL) / (s cosh(sL) + i delta sinh(sL))`, `t = s / (s cosh(sL) + i delta sinh(sL))`, `s^2 = kappa^2 - delta^2`

The transmitted wave also carries `exp(i beta_B L)`. The reflection seen from the far end follows from energy conservation: `r' = -conj(r) t / conj(t)`.
