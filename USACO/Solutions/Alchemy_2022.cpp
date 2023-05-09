#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <algorithm>
#include <cstring>


// Top bottom alchemy approach
using Metal = int;
using R_LIST = std::vector<Metal>;
Metal product;

typedef struct {
	std::vector<Metal> reactants;
	int reactantcount;
	Metal product;
}Transformation;


typedef struct {
	std::vector<Transformation> transformations;
	int t_count;
}T_LIST;

static inline T_LIST GetGiven() {

	T_LIST GivenTransformations;

	std::cin >> GivenTransformations.t_count;
	std::string str;
	Transformation tempTrans;
	tempTrans.product = 0;

	for (int i = 0; i <= product; ++i) {
		GivenTransformations.transformations.push_back(tempTrans);
	}

	for (int i = 0; i < GivenTransformations.t_count; ++i)
	{
		Transformation recipe;

		int product;
		std::cin >> product;
		recipe.product = (--product);

		int reactantcount;
		std::cin >> reactantcount;
		recipe.reactantcount = reactantcount;

		for (int reactantindex = 0; reactantindex < recipe.reactantcount; ++reactantindex) {
			int reactant;
			std::cin >> reactant;
			// Reactants stored by index and not id
			recipe.reactants.push_back(--reactant);
		}

		//GivenTransformations.transformations.push_back(recipe);
		GivenTransformations.transformations[product] = recipe;

		// Add transformation

	}
	return GivenTransformations;

}




static inline void UndoTransformation(R_LIST* resources, Transformation transformation) {
	for (int reactantindex = 0; reactantindex < transformation.reactantcount; ++reactantindex) {
		++(*resources)[transformation.reactants[reactantindex]];
	}
	--(*resources)[transformation.product];
};




static inline R_LIST TransformationToResource(Transformation* transformation, int prodNum) {
	R_LIST output(product + 1, 0);
	for (int i = 0; i < transformation->reactantcount; ++i) {
		output[transformation->reactants[i]] = prodNum;
	}
	return output;
}

// Using product recipe, list out required ingredites
// Starting from top ingredient, contstruct required number
// If all ingredients are successfully constructed, there are enough
// Repeat until convergence

// Returns false is ingredient is a base
bool ExpandResource(R_LIST * resources, Transformation* transformation, int tIndex) {
	if (transformation->product == 0) {
		return false;
	}

	int prodnum = (*resources)[tIndex];

	// Overflow
	if (prodnum > 1'000'000) {
		return false;
	}

	for (int compIndex = 0; compIndex <transformation->reactantcount; ++compIndex) {
		int compnum = transformation->reactants[compIndex];
		(*resources)[compnum] += prodnum;
	}
	(*resources)[tIndex] = 0;
	return true;
}

// Returns false if not enough
bool SubtractReactants(R_LIST* neededResources, R_LIST* givenResources, T_LIST* givenTransformations) {
	for (int resource = product; resource >= 0; --resource) {
		if ((*neededResources)[resource] == 0) {
			continue;
		}
		(*neededResources)[resource] = (*neededResources)[resource] - (*givenResources)[resource];
		if ((*neededResources)[resource] > 0) {
			if (!ExpandResource(&(*neededResources), &( (givenTransformations->transformations)[resource]), resource )) {
				return false;
			};
		};
	}
	return true;
}

// Helper function
bool IsEnough(R_LIST givenResources, T_LIST* givenTransformations, int prodNum) {
	R_LIST neededResources(product + 1, 0);
	neededResources[product] = prodNum;
	return SubtractReactants(&(neededResources), &(givenResources), givenTransformations);
};


int BinarySearch(R_LIST* givenResources, T_LIST* givenTransformations) {
	int low = 0;
	int high = 1'000'001;
SearchLoop:
	int test = (high + low) / 2;
	if (IsEnough(*givenResources, givenTransformations, test)) {
		low = test;
	}
	else {
		high = test;
	}

	if (low == (high - 1)) {
		return low;
	}
	else {
		goto SearchLoop;
	}
};




int main() {
	std::ios_base::sync_with_stdio(false);


	std::string str;
	// Initialize target
	std::cin >> product;
	// Get product by index not id.
	--product;

	// Initialize resources
	R_LIST resources = {};

	for (int resource = 0; resource <= product; ++resource) {
		int temp;
		std::cin >> temp;
		resources.push_back(temp);
	}

	// Initialize transformations
	T_LIST GivenTransformations = GetGiven();


	std::cout << BinarySearch(&(resources), &(GivenTransformations));


	return 0;
};













