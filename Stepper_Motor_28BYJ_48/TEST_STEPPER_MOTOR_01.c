
const int stepperPin_1 = 9;
const int stepperPin_2 = 10;
const int stepperPin_3 = 11;
const int stepperPin_4 = 12;

int stepNumber = 0;

/******************************/
/* Function */

void oneStep(bool dir) {
	if (dir)
	{
		switch(stepNumber) {
			case 0:
				digitalWrite(stepperPin_1, HIGH);
				digitalWrite(stepperPin_2, LOW);
				digitalWrite(stepperPin_3, LOW);
				digitalWrite(stepperPin_4, LOW);
			break;

			case 1:
				digitalWrite(stepperPin_1, LOW);
				digitalWrite(stepperPin_2, HIGH);
				digitalWrite(stepperPin_3, LOW);
				digitalWrite(stepperPin_4, LOW);
			break;

			case 2:
				digitalWrite(stepperPin_1, LOW);
				digitalWrite(stepperPin_2, LOW);
				digitalWrite(stepperPin_3, HIGH);
				digitalWrite(stepperPin_4, LOW);
			break;

			case 3:
				digitalWrite(stepperPin_1, LOW);
				digitalWrite(stepperPin_2, LOW);
				digitalWrite(stepperPin_3, LOW);
				digitalWrite(stepperPin_4, HIGH);
			break;
		}
	}
	else if (!dir)
	{
		switch(stepNumber) {
			case 0:
				digitalWrite(stepperPin_1, LOW);
				digitalWrite(stepperPin_2, LOW);
				digitalWrite(stepperPin_3, LOW);
				digitalWrite(stepperPin_4, HIGH);
			break;

			case 1:
				digitalWrite(stepperPin_1, LOW);
				digitalWrite(stepperPin_2, LOW);
				digitalWrite(stepperPin_3, HIGH);
				digitalWrite(stepperPin_4, LOW);
			break;

			case 2:
				digitalWrite(stepperPin_1, LOW);
				digitalWrite(stepperPin_2, HIGH);
				digitalWrite(stepperPin_3, LOW);
				digitalWrite(stepperPin_4, LOW);
			break;

			case 3:
				digitalWrite(stepperPin_1, HIGH);
				digitalWrite(stepperPin_2, LOW);
				digitalWrite(stepperPin_3, LOW);
				digitalWrite(stepperPin_4, LOW);
			break;
		}
	}

	++stepNumber;

	if (stepNumber > 3) {
		stepNumber = 0;
	}
}

/******************************/

void setup() {
	pinMode(stepperPin_1, OUTPUT);
	pinMode(stepperPin_2, OUTPUT);
	pinMode(stepperPin_3, OUTPUT);
	pinMode(stepperPin_4, OUTPUT);
}

void loop() {
	for (int i = 0; i < 1000; ++i)
	{
		oneStep(false);
		delay(2);
	}

	for (int i = 0; i < 1000; ++i)
	{
		oneStep(true);
		delay(2);
	}
}