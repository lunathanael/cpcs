#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <algorithm>
#include <cstring>


// Initialize class for metal

// Initialize solutions for all metals, making sure to define any metals that have not already been definied

// Using the metals given, compute the maximum amount of metals that can be made, going through each solution
using Metal = int;
using R_LIST = std::vector<Metal>;

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

	for (int i = 0; i < GivenTransformations.t_count; ++i)
	{
		Transformation recipe;
		
		int product;
		std::cin >> product;
		recipe.product = --product;

		int reactantcount;
		std::cin >> reactantcount;
		recipe.reactantcount = reactantcount;

		for (int reactantindex = 0; reactantindex < recipe.reactantcount; ++reactantindex) {
			int reactant;
			std::cin >> reactant;
			// Reactants stored by index and not id
			recipe.reactants.push_back(--reactant);
		}



		//// Get line
		//std::getline(std::cin, str);
		//std::stringstream ss(str);
		//std::string tempstring;

		//// Product
		//std::getline(ss, tempstring, ' ');
		//recipe.product = std::stoi(tempstring);

		//// Reactant number
		//std::getline(ss, tempstring, ' ');
		//recipe.reactantcount = std::stoi(tempstring);

		//while (std::getline(ss, tempstring, ' ')) {

		//	recipe.reactants.push_back(std::stoi(tempstring));
		//}

		GivenTransformations.transformations.push_back(recipe);

		// Add transofmration

	}
	return GivenTransformations;

}




static inline void UndoTransformation(R_LIST* resources, Transformation transformation) {
	for (int reactantindex = 0; reactantindex < transformation.reactantcount; ++reactantindex) {
		++(*resources)[transformation.reactants[reactantindex]];
	}
	--(*resources)[transformation.product];
};


static inline bool DoTransformation(R_LIST* resources, Transformation transformation) {
	++(*resources)[transformation.product];

	Transformation tempstore;
	tempstore.product = transformation.product;
	tempstore.reactantcount = 0;
	for (int reactantindex = 0; reactantindex < transformation.reactantcount; ++reactantindex) {
		if ((*resources)[transformation.reactants[reactantindex]] < 1) {
			UndoTransformation(resources, tempstore);
			return false;
		}
		--(*resources)[transformation.reactants[reactantindex]];
		tempstore.reactants.push_back(transformation.reactants[reactantindex]);
		++tempstore.reactantcount;
	}
	return true;
}

static inline int ProductCount(int product, R_LIST resources) {
	return resources[product];
}



static inline int MostProducts(int product, R_LIST* resources, T_LIST* recipes, std::vector<R_LIST>* memo) {
	if (std::find((*memo).begin(), (*memo).end(), *resources) != (*memo).end())
	{
		return 0;
	}

	(*memo).push_back(*resources);


	int bestCount = 0;
	int legal = 0;

	for (int transcount = 0; transcount < recipes->t_count; ++transcount) {
		if (!DoTransformation(resources, recipes->transformations[transcount])) {
			continue;
		}
		++legal;
		int count = MostProducts(product, resources, recipes, memo);
		UndoTransformation(resources, recipes->transformations[transcount]);
		bestCount = std::max(bestCount, count);
	}

	if (legal == 0) {
		return ProductCount(product, *resources);
	}

	return bestCount;
};



int main() {
	//std::ios_base::sync_with_stdio(false);

	std::string str;

	// Initialize target
	Metal product;
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


	std::vector<R_LIST>memo;

	std::cout << MostProducts(product, &resources, &GivenTransformations, &memo);


	return 0;
};
