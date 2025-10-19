#include <stdio.h>

int main() {
    float weight, height, bmi;
    char gender;

    printf("Enter gender (M/F): ");
    scanf(" %c", &gender);

    printf("Enter weight (in kilograms): ");
    scanf("%f", &weight);

    printf("Enter height (in meters): ");
    scanf("%f", &height);

    bmi = weight / (height * height);
    printf("\nYour BMI is: %.2f\n", bmi);

    if (bmi < 18.5) {
        printf("Status: Underweight\n");
    } else if (bmi >= 18.5 && bmi <= 24.9) {
        printf("Status: Normal weight\n");
    } else if (bmi >= 25 && bmi <= 29.9) {
        printf("Status: Overweight\n");
    } else if (bmi >= 30) {
        printf("Status: Obese\n");
    } else {
        printf("Invalid input.\n");
    }
    
    if (bmi >= 25) {
        if (gender == 'M' || gender == 'm')
            printf("Health Tip: Men should aim for more cardio exercises.\n");
        else if (gender == 'F' || gender == 'f')
            printf("Health Tip: Women should include balanced diet and light exercise.\n");
        else
            printf("Unknown gender, general advice: Stay active and eat healthy.\n");
    }
    
    const char *risk = (bmi < 18.5) ? "Risk: Nutrient deficiency" :
                       (bmi <= 24.9) ? "Risk: Low risk" :
                       (bmi <= 29.9) ? "Risk: Moderate risk" :
                       "Risk: High risk";

    printf("%s\n", risk);

    return 0;
}