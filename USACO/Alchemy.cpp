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


class Transformations {
public:
	T_LIST GivenTransformations;

	// Initial call to define transformations
	Transformations()
	{
		std::string str;
		std::getline(std::cin, str);
		GivenTransformations.t_count = std::stoi(str);

		for (int i = 0; i < GivenTransformations.t_count; ++i)
		{
			Transformation recipe;

			// Get line
			std::getline(std::cin, str);
			std::stringstream ss(str);
			std::string tempstring;

			// Product
			std::getline(ss, tempstring, ' ');
			recipe.product = std::stoi(tempstring);

			// Reactant number
			std::getline(ss, tempstring, ' ');
			recipe.reactantcount = std::stoi(tempstring);

			while (std::getline(ss, tempstring, ' ')) {

				recipe.reactants.push_back(std::stoi(tempstring));
			}

			GivenTransformations.transformations.push_back(recipe);

			// Add transofmration

		}

	}
	T_LIST GetAllTransformations(R_LIST resources)
	{
		T_LIST output;
		output.t_count = 0;
		for (int recipeindex = 0; recipeindex < GivenTransformations.t_count; ++recipeindex) {
			Transformation currentrecipe = GivenTransformations.transformations[recipeindex];
			if (IsEnoughReactants(resources, currentrecipe)) {
				output.transformations.push_back(currentrecipe);
				++output.t_count;
			}

		}
		return output;
	}

private:
	bool IsEnoughReactants(R_LIST resources, Transformation transformation) {
		for (int reactantindex = 0; reactantindex < transformation.reactantcount; ++reactantindex) {
			if (resources[transformation.reactants[reactantindex]] == 0) {
				return false;
			}
		}
		return true;
	}
};


void UndoTransformation(R_LIST* resources, Transformation transformation) {
	for (int reactantindex = 0; reactantindex < transformation.reactantcount; ++reactantindex) {
		++(*resources)[transformation.reactants[reactantindex]];
	}
	--(*resources)[transformation.product];
};


bool DoTransformation(R_LIST* resources, Transformation transformation) {
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

int ProductCount(int product, R_LIST resources) {
	return resources[product];
}



int MostProducts(int product, R_LIST resources, Transformations transformations, std::vector<R_LIST>*memo) {
	if (std::find((*memo).begin(), (*memo).end(), resources) != (*memo).end())
	{
		return 0;
	}


	int bestCount = 0;
	int legal = 0;

	for (int transcount = 0; transcount < transformations.GivenTransformations.t_count; ++transcount) {
		if (!DoTransformation(&resources, transformations.GivenTransformations.transformations[transcount])) {
			continue;
		}
		++legal;
		int count = MostProducts(product, resources, transformations, memo);
		(*memo).push_back(resources);
		UndoTransformation(&resources, transformations.GivenTransformations.transformations[transcount]);
		bestCount = std::max(bestCount, count);
	}

	if (legal == 0) {
		return ProductCount(product, resources);
	}

	return bestCount;
};



int main() {
	std::string str;

	// Initialize target
	Metal product;
	std::getline(std::cin, str);
	product = std::stoi(str);

	// Initialize resources
	R_LIST resources = { 0 };

	std::getline(std::cin, str);
	std::stringstream ss(str);
	std::string tempstring;

	int temp = 0;
	while (std::getline(ss, tempstring, ' ')) {
		resources.push_back(stoi(tempstring));
	}

	// Initialize transformations
	Transformations recipes;
	std::vector<R_LIST>memo;
	std::cout << MostProducts(product, resources, recipes, &memo);

	return 0;
};
