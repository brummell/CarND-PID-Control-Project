# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## PID Control
The proportional term controls the attack rate of the controller: the higher the proportional gain, the more aggressively the controller will try to counteract any errors. If this is set too low, the controller will be too slow to react to error, and in particular, if the environment is highly dynamic, the controller will be essentially thrown into chaos as long before it has finished correcting one error state (e.g. slightly left of center, steering perpendicular to the road, on a straightaway), the system under control may have mean while "drifted" into a completely new state (e.g. approximately centered, but now steering slightly right of center, on a road that is turning quickly left). Conversely, if it is set too high, it will often correct too strongly close to the target, which in our case would have the car actually crossing the centerline, creating a state in which the error is now of the opposite polarity; this leads to oscillatory behavior around the target and, in the case of a large initial error, possibly even divergent behavior. The time scales around actuation and measurement, as well as the dynamics of the error measure, seem to play a strong role in determining how tolerable a high P-gain value is.    

The derivative term corrects the proportional control term by decreasing the overall error as the "derivative" of the error (the simple error delta in our case) decreases. This allows us to correct large errors quickly (via a higher P-gain) by damping the trajectory as we near our target (i.e. smaller errors); ideally, this should eliminate troublesome oscillatory behavior. Too small a K-gain, and we find ourselves stuck with the old non-convergent behavior ("underdamped); too high, and we find that the buffering of our correction is too strong and the responsiveness of the system is inadequate for many enviornments ("overdamped"); at the ideal value, the system will act quickly to get on target, but will do so smoothly and monotonically ("critically damped"). Interestingly, I believe that in my experience, an overly high D-gain caused seemingly oscillatory behavior, as (similar to the case described above) an underreactive system in a quickly changing environment creates a very chaotic error signal. In our example, this seemingly oscillatory behavior was very confusing while I was hand-tuning the parameters the first time, as I interpreted it as an overly strong P-gain, not considering the actual environment of the problem.

The integral term is primarily for correcting systemic errors such as poorly calibrated actuator or dynamic environmental forces such as a crosswind. It accomplishes this by accumulating small bits of error at each step, which allows it to eventually "notice" and correct biases in the control. Too large a value, and it will be overly active, trying to correct white or nearly-white noise. Too small an I-gain value, and the controller may not be able to compensate for the relevant systemic errors before they change polarity, force a serious incident, etc..

## Project Tuning Methodology
Despite an appreciation for automated optimization, in this case I found it more education to hand tune the parameters, observing the results as I went along. At first this was rather punishing, and likely untenable for any real-life usage, but after learning more about the PID controller in terms of oscillatory behavior, divergence, and damping, I found a fairly good method for approaching the problem by hand: using just the proportional term, I increased the gain until the system was adequately responsive and just barely oscillatory; I then added the derivative term to dampen the near-target behavior, increasing it to improve smoothness and convergence until it slowed the responsiveness too much to handle environmental changes, at which point I just pulled it back; finally I added a very small integral term, which required no tuning as the simulator doesn't seem to have much in terms of bias, I was careful to observe the car for a few laps to ensure the integral portion wasn't accumulating error from bias in the terms of the car's path around the track). 

Again, I did run into the issue mentioned above of an overly high derivative term giving the appearance of oscillatory response behavior, but once I started using the above methodology on a straightaway first, making necessary adjustments for more dynamic track portions, it became fairly straightforward. 

Although I did actually find this process rather effective at drilling home the principles of PID control, I would much prefer high-repetition, fast simulation with an optimization algorithm, and will likely implement twiddle once I have a bit of free time.
