# Vibrating string

The task is to determine the shape of a homogeneous vibrating string fixed at both ends. Let us assume that the string has a length $l \in \mathbf{R}^+$ and vibrates in the transverse plane. By selecting an appropriate coordinate system, the shape of the string can be expressed as:

$$
    u : [0, \, l] \times \mathbf{R}_0^+ \to \mathbf{R}
$$

where $u(x, t) \in \mathbf{R} \, \, \big((x, \, t) \in [0, l] \times \mathbf{R}_0^+\big)$ refers to the displacement of the string at point $x$ at time $t$.

If $u \in D^2$ ($u$ is twice differentiable), then (based on physical considerations) it satisfies the partial differential equation with the constant $q \in \mathbf{R}^+$:

$$
    \partial_{22} u = q \cdot \partial_{11} u,
$$

which is a (special) partial differential equation. Given the initial shape of the string and its velocity $\big(u(x, 0) \text{ and } \partial_2 u(x, 0) \text{ for }  x \in [0, l] \big)$, the function $u$ can be determined.

The results obtained from ordinary differential equations can often be successfully applied when solving partial differential equations. Thus, the above equation can also model the motion of a vibrating string. Let $u \in C^2$ ($u$ is twice continously differentiable) and given
$$
    f, \, g \in \mathbf{R} \to \mathbf{R}
$$
functions, such that they satisfy the following boundary and initial conditions:

$$
\begin{array}{ll}
(\mathfrak{1}) \quad u(0, \, t) = u(l, \, t) = 0 & (t \in \mathbf{R}^+_0), \\
\\
(\mathfrak{2}) \quad u(x, \, 0) = f(x) & (x \in [0, \, l]), \\
\\
(\mathfrak{3}) \quad \partial_2u(x, \, 0) = g(x) & (x \in [0, \, l]).
\end{array}
$$

Based on the work of *Euler*, *Lagrange*, *D'Alembert*, *D. Bernoulli*, and finally *Fourier*, the following method was refined (applicable to many similar problems). The fundamental idea is to seek the solution $ u $ in the form:

$$
    u(x, t) = F(x) \cdot G(t) \quad  \big((x, \, t) \in [0, \, l] \times \mathbf{R}_0^+ \big)
$$

(known as the *Fourier method*), where $F, G \in \mathbf{R} \to \mathbf{R}$ are (suitable) functions that are twice continuously differentiable. By omitting the details, this problem can be reduced to a homogeneous linear second-order differential equation with constant coefficients.

It can be easily verified that for any $n \in \mathbf{N}$ and parameters $a_n, b_n, d_n \in \mathbf{R}$, the functions

$$
u_n(x, t) := d_n \sin\left(\frac{n \pi x}{l}\right) \cdot \left(a_n \cos\left(\frac{\pi \sqrt{q} n t}{l}\right) + b_n \sin\left(\frac{\pi \sqrt{q} n t}{l}\right)\right) \quad \big((x, \, t) \in [0, \, l] \times \mathbf{R}_0^+ \big)
$$
are solutions (for the criteria $(\mathfrak{1})$). Let us note that under suitable conditions, the function

$$
u(x, t) := \sum_{n=0}^\infty u_n(x, t) \quad \big((x, \, t) \in [0, \, l] \times \mathbf{R}_0^+ \big)
$$

(function series sum) also exists as a solution, and the initial conditions take the following forms:

$$
\begin{array}{ll}
\displaystyle u(x, 0) = \sum_{n=0}^\infty a_n d_n \cdot \sin\left(\frac{n \pi x}{l}\right) = f(x) & (x \in [0, l]),\\
\\
\displaystyle  \partial_2 u(x, 0) = \frac{\pi \sqrt{q}}{l} \cdot \sum_{n=0}^\infty b_n d_n \cdot n \cdot \sin\left(\frac{n \pi x}{l}\right) = g(x) & (x \in [0, l]).
\end{array}
$$

Thus, these equalities imply that $f$ and $g$ represent the Fourier series expansions (specifically sine series) of the functions $f$ and $g$.

## Applying the results

In my example, I used the results for a much simpler case. Let $l, \, h \in \mathbf{R}^+$ represent the length of the string and the *initial height of the string*, respectively. The initial shape and velocity ($f$ and $g$ in the previous section) of the string is determined by the functions that satisfy the following criterias:
$$
    f : [0, \, l] \to \mathbf{R}, \quad f(x) := ax^2 + bx + c \quad (x \in [0, \, l], \, a, \, b, \, c \in \mathbf{R})
$$
and
$$
    f(0) = 0, \, f(l) = 0, \, f(l/2) = h.
$$
This problem is straightforward to solve using simple interpolation:
$$
    f(x) = - \frac{Q}{l}x^2 + Qx  \quad (x \in [0, \, l]),
$$
where $ Q := \frac{4h}{l} $. Also, let the velocity function $g$ be as follows
$$
    g : [0, \, l] \to \mathbf{R}, \quad g(x) := -f(x) \quad (x \in [0, \, l]).
$$
The last task left is to - for every $n \in \mathbf{N}$ - determine the coefficients $a_n$, $b_n$ and $c_n$ from the previous section by expanding the functions $f$ and $g$ into sine series. Again, by omitting the details this can be done quite easily. For every $n \in \mathbf{N}^+$, let
$$
\begin{array}{ll}
a_n := -1,\\
\\
b_n := \displaystyle \frac{l}{n \sqrt{q} \pi},\\
\\
d_n := \displaystyle \frac{4l Q\big( (-1)^n - 1 \big)}{\pi^3n^3}.
\end{array}
$$
Thus,
$$
    f(x) = \sum_{n=1}^\infty a_n d_n \sin\left(\frac{\pi n x}{l}\right) \quad (x \in [0, \, l]),
$$
and
$$
    g(x) = \frac{\pi \sqrt{q}}{l} \sum_{n=1}^\infty b_n d_n n \sin\left(\frac{\pi n x}{l}\right) \quad (x \in [0, \, l]).
$$
Finally, the function
$$
    u : [0, \, l] \to \mathbf{R}^+_0 \to \mathbf{R}
$$
takes the form
$$
u(x, t) := \sum_{n=1}^\infty u_n(x, t) \quad \big((x, \, t) \in [0, \, l] \times \mathbf{R}_0^+ \big),
$$
where - for every $n \in \mathbf{N}^+$ and $(x, \, t) \in [0, \, l] \times \mathbf{R}_0^+$ - the $u_n$ functions are defined the same as in the previous section:
$$
    u_n(x, \, t) := \underbrace{\frac{4l Q\big( (-1)^n - 1 \big)}{\pi^3n^3}}_{d_n} \sin\left(\frac{n \pi x}{l}\right) \cdot \Bigg(\underbrace{(-1)}_{a_n}\cos\left(\frac{\pi \sqrt{q} n t}{l}\right) + \underbrace{\frac{l}{n \sqrt{q} \pi}}_{b_n} \sin\left(\frac{\pi \sqrt{q} n t}{l}\right)\Bigg).
$$

