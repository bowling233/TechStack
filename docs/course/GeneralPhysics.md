# General Physics

## L3: Newton's Laws

本章讲解内容：

<!-- prettier-ignore-start -->
!!! note "Newton's Laws"
    

    1. In the absence of external forces, an object at rest remains at rest and an object in motion continues in motion with a constant velocity.
    2. $\sum \mathbf{F} = m \mathbf{a}$
    3. The action force is equal in magnitude to the reaction force and opposite in direction.
    4. 
<!-- prettier-ignore-end -->

The book mentioned something related to *reference frame*:

- A reference frame requires a **coordinate system** and a set of **clocks**.
- Newton's first law allows us to choose special family of reference frames in which *all* observers would measure the *same* acceleration:

<!-- prettier-ignore-start -->
!!! info "inertial frames"
    
    If the net force acting on a body is zero, then it is possible to find a set of reference frames in which that body has no acceleration.
<!-- prettier-ignore-end -->

Next we will explore some form of motions.

- Free Fall
- Projectile Motion

Projectile motion can be seen as free fall. This is an example that **all inertial observers agree on measurements of acceleration**.

<!-- prettier-ignore-start -->
??? info "Galilean Transformation"
    
    We can deduce the result that all inertial observers agree on measurements of acceleration using Galilean transformation:
    
    $\mathbf{r'} = \mathbf{r} - \mathbf{v_0}t$
<!-- prettier-ignore-end -->

- Relative Motion in noninertial frames

<!-- prettier-ignore-start -->
!!! info "Example of pseudoforce "
    
    - centrifugal force: directed away from the center

<!-- prettier-ignore-end -->

## L4: Work and Kinetic Energy

<!-- prettier-ignore-start -->
!!! abstract
    
    - **Work** done by a constant/varying force.
    - Kinetic energy.
    - Work-kinetic energy theorem.
    - Power: the time rate of doing work.
<!-- prettier-ignore-end -->

### Word List

| English    | Chinese                                                      |
| ---------- | ------------------------------------------------------------ |
| kinematic  | 运动学的                                                     |
| drag force[^1] | 阻力 <br /> |
| deviation  | 偏差                                                         |
| agent | 施力者 |
| exert | 施加 |
| perpendicular | 垂直的 |
| interplanetary | 行星间的 |
| equilibrium | 平衡 |
| equili- | equilibrant, equilibrate, equilibrist, equilibration, disequilibrate, ... | 

[^1]:{produced by the deviation or difference in velocity between the fluid and the object}

### Review

We've learn't to use **Newton's Laws and Kinematics** to solve problems in case of $a = a(t)$. But how to solve the the case in which $a=a(x)$?

### Contents

- Definition of **work**

In what situation a force does no work?

Scalar product of two vectors.

Work done by a varying force: $\int^{x_f}_{x_i}F_x\mathrm{d}x$. Determine from graphical and analytical prespective.

- Spring: Hooke's Law

Restoring force. Work done by a spring.

- Kinetic Energy

Derive the expression of kinetic energy in case of constant acceleration.

$$
W = (ma)d\\
d=?, a=?\\
W=\frac12mv_f^2
$$
Proof in the generic case.
$$
W=\int^{x_f}_{x_i}ma_x\mathrm{d}x\\
a=\frac{\mathrm{d}v}{\mathrm{d}t}=?\\
W=\frac12mv^2_f-\frac12mv^2_i
$$

- Power

Average power and instantaneous power. Write their expression respectively.

What's $1\mathrm{kWh}$. What amount of $J$ is it equivalent to?

- Kinetic Energy at High Speed

$$
\begin{align}
K &= mc^2(\frac1{\sqrt{1-(v/c)^2}}-1)\\
  &= \frac12mv^2\ \ \text{for}\ \ \frac{v}c<<1
\end{align}
$$


## [Doing] L5: Conservation of Energy

<!-- prettier-ignore-start -->
!!! abstract

    - Potential energy
    - Conservative forces
    - Conservation of (mechanical) energy
<!-- prettier-ignore-end -->

- WordList:

| English | Chinese |
| - | - |
| deform | 使畸形 |
