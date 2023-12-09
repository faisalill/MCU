<script>
  import { onMount } from "svelte";
  let rotation = { alpha: 0, beta: 0, gamma: 0 };
  let motion = { X: 0, Y: 0, Z: 0 };

  // Check if DeviceOrientationEvent is supported
  onMount(() => {
    if ("ondeviceorientation" in window) {
      window.addEventListener("deviceorientation", handleOrientation, false);
    } else {
      console.log("DeviceOrientationEvent is not supported");
    }

    if ("ondevicemotion" in window) {
      window.addEventListener("devicemotion", handleMotion, false);
    } else {
      console.log("DeviceMotionEvent is not supported");
    }
  });

  function handleOrientation(event) {
    // Extract rotation data
    const newRotation = {
      alpha: event.alpha, // rotation around the z-axis
      beta: event.beta, // rotation around the x-axis
      gamma: event.gamma, // rotation around the y-axis
    };
    // Force Svelte to update the component
    rotation = newRotation;
  }

  function handleMotion(event) {
    const newMotion = {
      X: event.acceleration.x,
      Y: event.acceleration.y,
      Z: event.acceleration.z,
    };

    motion = newMotion;
  }
</script>

<main>
  <h1>Device Rotation</h1>
  <p>Alpha (Z-axis): {rotation.alpha.toFixed(2)}</p>
  <p>Beta (X-axis): {rotation.beta.toFixed(2)}</p>
  <p>Gamma (Y-axis): {rotation.gamma.toFixed(2)}</p>
</main>

<main>
  <h1>Device Motion</h1>
  <p>X: {motion.X.toFixed(2)}</p>
  <p>Y: {motion.Y.toFixed(2)}</p>
  <p>Z: {motion.Z.toFixed(2)}</p>
</main>

<style>
  /* Add any styling as needed */
</style>
