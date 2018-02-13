main() {

	int ones = 0;
	int tens = 0;
	int hundreds = 0;
	int thousands = 0;
	int tenthousands = 0;
	long km = 0;
	
	for(tenthousands = 0; tenthousands < 10; tenthousands++) {
		for (thousands = 0; thousands < 10; thousands++) {
			for (hundreds = 0; hundreds < 10; hundreds++) {
				for (tens = 0; tens < 10; tens++) {
					for (ones = 0; ones < 10; ones ++) {
						km = 10000*tenthousands + 1000 * thousands + 100 * hundreds + 10 * tens + ones;
					}
				}
			}
		}
	}
}
