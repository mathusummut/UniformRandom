public class UniformRandom {
	private static long[] seeds = new long[56];
	private static int index;

	static {
		long seed = 694940303115278604L - System.currentTimeMillis();
		seeds[55] = seed;
		long num = 1L;
		for (int num1, i = 1; i < 55; i++) {
			num1 = 21 * i % 55;
			seeds[num1] = num;
			num = seed - num;
			seed = seeds[num1];
		}
		int j;
		for (int i = 1; i < 5; i++) {
			for (j = 1; j < 56; j++)
				seeds[j] -= seeds[1 + (j + 30) % 55];
		}
	}

	public static byte getByte() {
		return (byte) (getLong() % 256);
	}

	public static long getLong() {
		int index = ++UniformRandom.index % 56;
		long value = seeds[index] - seeds[(index + 21) % 56];
		seeds[index] = value;
		return Math.abs(value);
	}

	public static double getDouble() {
		return getLong() * 10.84202172485504434066227518411056086827404260683377e-20;
	}

	public static double toInterval(long value, double min, double max) {
		if (min > max) {
			double temp = min;
			min = max;
			max = temp;
		}
		return (Math.abs(value) * 10.84202172485504434066227518411056086827404260683377e-20) * (max - min) + min;
	}
}