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

static inline T_LIST GetGiven(int product) {

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


// Function to break down resources to base componenets

void printRLIST(R_LIST resources) {
	std::cout << "RESOURCE LIST: " << std::endl;
	for (int resource = 0; resource < resources.size(); ++resource) {
		std::cout << resources[resource] << " ";
	}
	std::cout << std::endl;
}

void InitializeResources(R_LIST* resources, T_LIST transformations) {
	for (int tIndex = resources->size() - 1; tIndex >= 0; --tIndex) {
		int prodnum = (*resources)[tIndex];
		if ((transformations.transformations[tIndex].product == 0) || (prodnum == 0)) {
			continue;
		}
		for (int compIndex = 0; compIndex < transformations.transformations[tIndex].reactantcount; ++compIndex) {
			int compnum = transformations.transformations[tIndex].reactants[compIndex];
			(*resources)[compnum] += prodnum;
		}
		(*resources)[tIndex] = 0;
	}
}


// Function to break down final recipe to base components
R_LIST BreakRecipe(int product, T_LIST transformations) {
	R_LIST output;
	R_LIST productTransformation = transformations.transformations[product].reactants;

	for (int i = 0; i < productTransformation.size(); ++i) {
		for (int j = output.size(); j < productTransformation[i]; ++j) {
			output.push_back(0);
		}
		output.push_back(1);
	}
	output.resize(product + 1);


	InitializeResources(&output, transformations);
	return output;
}



static inline int MostProducts(R_LIST resources, T_LIST transformations, int product) {
	InitializeResources(&resources, transformations);
	R_LIST productRecipe = BreakRecipe(product, transformations);
	int leastSoFar = INT32_MAX;

	printRLIST(productRecipe);
	printRLIST(resources);

	for (int i = 0; i <= product; ++i) {
		if (productRecipe[i] == 0) {
			continue;
		}
		int count = resources[i] / productRecipe[i];
		leastSoFar = std::min(count, leastSoFar);
	}
	if (leastSoFar == INT32_MAX) {
		return 0;
	}
	return leastSoFar;
};


int main() {
	std::ios_base::sync_with_stdio(false);

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
	T_LIST GivenTransformations = GetGiven(product);



	std::cout << MostProducts(resources, GivenTransformations, product);


	return 0;
};
