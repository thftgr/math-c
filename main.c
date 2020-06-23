
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int ComputetotalHits(int* n300, int* n100, int* n50, int* nMiss) {
	return (*n300 + *n100 + *n50 + *nMiss);
}

double computeAccuracyValue(int* countHitCircles, int* mods, int* n300, int* n100, int* n50, int* totalHits, double* od) {
	// This percentage only considers HitCircles of any value - in this part of the calculation we focus on hitting the timing hit window
	double betterAccuracyPercentage;
	int amountHitObjectsWithAccuracy = *countHitCircles;

	if (amountHitObjectsWithAccuracy > 0) betterAccuracyPercentage = ((*n300 - (*totalHits - amountHitObjectsWithAccuracy)) * 6 + *n100 * 2 + *n50) / (double)(amountHitObjectsWithAccuracy * 6);
	else betterAccuracyPercentage = 0;

	// It is possible to reach a negative accuracy with this formula. Cap it at zero - zero points
	if (betterAccuracyPercentage < 0) betterAccuracyPercentage = 0;

	// Lots of arbitrary values from testing.
	// Considering to use derivation from perfect accuracy in a probabilistic manner - assume normal distribution
	double accuracyValue = (pow(1.52163, *od)) * (pow(betterAccuracyPercentage, 24)) * 2.83;

	// Bonus for many hitcircles - it's harder to keep good accuracy up for longer
	accuracyValue *= fmin(1.15, pow(amountHitObjectsWithAccuracy / 1000.0, 0.3));

	if ((*mods & 8) != 0)
		accuracyValue *= 1.08;
	if ((*mods & 1024) != 0)
		accuracyValue *= 1.02;

	return accuracyValue;
}

//double computeSpeedValue(double* speedStars, int* totalHits, int* nMiss, int* beatmapMaxCombo, int* scoreMaxCombo) {
//
//	double speedValue = pow(5.0 * fmax(1.0, *speedStars / 0.0675) - 4.0, 3.0) / 100000.0;
//
//	// Longer maps are worth more
//	speedValue *= 0.95 + 0.4 * fmin(1.0, *totalHits / 2000.0) +
//		(*totalHits > 2000 ? log10(*totalHits / 2000.0) * 0.5 : 0.0);
//
//	// Penalize misses exponentially. This mainly fixes tag4 maps and the likes until a per-hitobject solution is available
//	speedValue *= pow(0.97, nMiss);
//
//	// Combo scaling
//	if (*beatmapMaxCombo > 0)
//		speedValue *= fmin(pow(*scoreMaxCombo, 0.8) / pow(beatmapMaxCombo, 0.8), 1.0);
//
//	double approachRateFactor = 1.0;
//	if (*ar > 10.33)
//		approachRateFactor += 0.3 * (ar - 10.33);
//
//	speedValue *= approachRateFactor;
//
//	if ((*mods & 8) == 8)
//		speedValue *= 1.0 + 0.04 * (12.0 - ar);
//
//	// Scale the speed value with accuracy _slightly_
//	speedValue *= 0.02 + *accuracy;
//	// It is important to also consider accuracy difficulty when doing that
//	speedValue *= 0.96 + pow(od, 2) / 1600;
//
//	return speedValue;
//}




void main() {
	//int mods = 1;
	//int* modsp = &mods;


	//printf("%p\n",&mods); // mods 의 주소
	//printf("%p\n",modsp); // 포인터 modsp 가 가진 mods 의 주소
	//printf("%p\n",*modsp);// 포인터 modsp 가 가진 mods 의 값

	enum Mods
	{
		None = 0,
		NoFail = 1,
		Easy = 1 << 1,
		TouchDevice = 1 << 2,
		Hidden = 1 << 3,
		HardRock = 1 << 4,
		SuddenDeath = 1 << 5,
		DoubleTime = 1 << 6,
		Relax = 1 << 7,
		HalfTime = 1 << 8,
		Nightcore = 1 << 9, // Only set along with DoubleTime. i.e: NC only gives 576
		Flashlight = 1 << 10,
		Autoplay = 1 << 11,
		SpunOut = 1 << 12,
		Relax2 = 1 << 13,    // Autopilot
		Perfect = 1 << 14, // Only set along with SuddenDeath. i.e: PF only gives 16416  
		Key4 = 1 << 15,
		Key5 = 1 << 16,
		Key6 = 1 << 17,
		Key7 = 1 << 18,
		Key8 = 1 << 19,
		FadeIn = 1 << 20,
		Random = 1 << 21,
		Cinema = 1 << 22,
		Target = 1 << 23,
		Key9 = 1 << 24,
		KeyCoop = 1 << 25,
		Key1 = 1 << 26,
		Key3 = 1 << 27,
		Key2 = 1 << 28,
		ScoreV2 = 1 << 29,
		Mirror = 1 << 30,
		KeyMod = Key1 | Key2 | Key3 | Key4 | Key5 | Key6 | Key7 | Key8 | Key9 | KeyCoop,
		FreeModAllowed = NoFail | Easy | Hidden | HardRock | SuddenDeath | Flashlight | FadeIn | Relax | Relax2 | SpunOut | KeyMod,
		ScoreIncreaseMods = Hidden | HardRock | DoubleTime | Flashlight | FadeIn
	};

	


	int countHitCircles = 400;
	int mods = 0;
	int n300 = 400;
	int n100 = 0;
	int n50 = 0;
	int nMiss = 0;
	double od = 9.7;
	int totalHits = ComputetotalHits(&n300, &n100, &n50, &nMiss);
	double d = computeAccuracyValue(&countHitCircles, &mods, &n300, &n100, &n50, &totalHits, &od);

	printf("%.2f\n", d);
	

	printf("%d", ScoreIncreaseMods);

}

