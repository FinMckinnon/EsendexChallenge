#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "StringManipulation.h"

// Deals with information about individual items
struct Item
{
	double price,
		rulePrice;
	int ruleQuantity,
		amount = 0;
	bool checked = false;

	void assignValues(std::vector<std::string> itemInformation)
	{
		price = atof(itemInformation[1].c_str());
		ruleQuantity = atof(itemInformation[2].c_str());
		rulePrice = atof(itemInformation[3].c_str());
	}

};

// Holds data and processes relevant to a discounting process
class ECC
{
public:
	std::string legalItems;
	std::vector<Item> newItemInfo;
	std::vector<char> basket;
	double totalPrice;
	ECC(std::string fileName);

	void ScanItems()
	{
		std::string itemScanned;

		std::cout << "\nPlease type item codes in, you can type multiple at once or single items at a time. \nPress space to add the item(s). \n \nWhen done please enter '0' and press enter. \n \nReady to scan items..." << std::endl;
		while (true)
		{
			std::cin >> itemScanned;
			itemScanned = sm.ToUpper(itemScanned);
			if (itemScanned == "0") break;
			else
			{
				addToBasket(itemScanned);
			}
		}
		std::cout << std::endl;
	}

	// Calculates total price of the purchase
	double CalculateTotalPrice()
	{
		double basketCost;

		basketCost = total();
		showCheckoutInfo(basket, basketCost);

		return basketCost;
	}

private:

	stringManipulation sm;

	// Adds an item to the basket, increments the amount of specified item
	void addToBasket(std::string itemToAdd)
	{
		std::string itemInBasket;
		int itemID,
			length = itemToAdd.length();


		for (int charCount = 0; charCount < length; charCount++)
		{
			// Exclude characters that are not within the pricingRules file
			if (legalItems.find(itemToAdd[charCount]) != std::string::npos)
			{
				itemID = (int)itemToAdd[charCount] - 65;
				newItemInfo[itemID].amount++;
				if (newItemInfo[itemID].amount != 0) basket.push_back(itemToAdd[charCount]);
			}
			else
			{
				std::cout << "Unidentified item scanned '"<< itemToAdd[charCount] <<"'" << std::endl;
			}
		}
	}

	// Totals the price of the items in the basket
	double total()
	{
		int itemID,
			amountOfItem,
			amountOfDeal;
		double dealPrice,
			standardPrice,
			cost = 0;
		std::vector<char> checked;
		Item item;

		for (int itemInBasket = 0; itemInBasket < basket.size(); itemInBasket++)
		{
			//Use ASCII to convert character to index of pricingRules
			itemID = (int)basket[itemInBasket] - 65;

			item = newItemInfo[itemID];
			// Checks to see if the item has already been put through
			if (item.checked == false)
			{
				//Find the amount of item being brought and how many rules apply
				amountOfItem = item.amount;
				amountOfDeal = amountOfItem / item.ruleQuantity;

				dealPrice = (amountOfDeal * item.rulePrice);
				standardPrice = (amountOfItem % item.ruleQuantity)*item.price;

				cost += dealPrice + standardPrice;
				newItemInfo[itemID].checked = true;
			}
		}
		return cost / 100;
	}

	// Gives a checkout infromation screen to the user
	void showCheckoutInfo(std::vector<char> items, double itemCost)
	{
		std::string allItems;
		allItems = sm.concatChar(items);
		//Shorten string to avoid interference with UI
		if (allItems.length() > 15) allItems = allItems.substr(0, 13) + "...";
		std::cout << std::setw(21) << std::left << "Items" << std::setw(21) << "Total" << std::endl;
		std::cout << std::setw(21) << std::left << allItems << std::setw(21) << std::fixed << std::setprecision(2) << itemCost << std::endl << std::endl;
	}

};

// Takes pricing rules from a formatted text file and assigns them to items struct
ECC::ECC(std::string fileName)
{
	Item newItem;
	std::vector<Item> fullPricingRules;
	int itemNumber = 0;

	std::ifstream pricingRulesFile(fileName + ".txt");
	for (std::string line; getline(pricingRulesFile, line);)
	{
		std::vector<std::string> itemInformation = sm.splitString(line);
		newItemInfo.push_back(newItem);
		newItemInfo[itemNumber].assignValues(itemInformation);
		std::string str;
		legalItems += itemInformation[0];
		itemNumber++;
	}
}