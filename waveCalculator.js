/*
 * Calculate wave
 * 
 * Inputs:
 *   time [s]; frequency [Hz]; amplitude [decimal]; phaseShift [degree];
 */
function wave(time, frequency, amplitude, phaseShift) {
	function freq(hertz) {
		return hertz * Math.PI * 2;
	}

	function radian(degree) {
		return degree * (Math.PI / 180);
	}

	return amplitude * Math.sin(freq(frequency) * time + radian(phaseShift));
}
