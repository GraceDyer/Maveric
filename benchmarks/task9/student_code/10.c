int f(int x) {
	int sum = 1;
	while (x > 0) {
		if (x % 10 != 0) {
			sum *= x % 10;
		}
		x /= 10;
	}
	if (sum >= 10) {
		sum = f(sum);
	}
	else {
		return sum;
	}

}
