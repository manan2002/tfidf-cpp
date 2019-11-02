#include <iostream>
#include "summarizer.h"

int main(){
	string s = "Pollution in Delhi is a perpetual problem which need to be looked upon as a serious issue not only by the Government but also by the citizens of the city.One of the easiest ways is that there should be an efficient involvement of Resident Welfare Associations in various localities in collection, segregation of garbage from houses and the societies.Citizens can take steps to covert the garbage into compost in their localities.More and more trees must be planted in every locality.Every individual should keep a proper check on the pollution level of their vehicles.Making more use of CNG.One of the best ways to control pollution is to manage wastes of all types in a proper manner.Each and every citizen should abide by the 3Rs: Recycle, Reuse, Reduce.More and more people should use bus and metro instead of cars and scooters, as they can carry a lot more people in one journey. Car pool is also a good option.Controlling the use of energy and making use of electricity in an efficient manner.One can also reduce water pollution by reducing the use of chemicals, cleaning agents, pesticides, herbicides, fertilizers etc.It is the duty of every citizen to think in a broader perspective to control pollution. We really don’t want our future generations to live in an unhealthy environment in Delhi. We really don’t want our children or our elders to get into incessant coughing due to pollution. Like we say charity begins at home, I take a pledge to do what I can for my environment and protect it to the best I can. If each one of us takes a pledge to do our bit for our environment, I am sure Delhi will be a better place to live in. Even asmall step counts.";
	vector<string> sentences = getSentences(s);
	vector<pair<int, double>> summary = getSummary(s);
	int count = 0;
	int numLines = 5; //Change this variable to match how many lines are needed in summary.
	for (auto pair : summary){
		cout << sentences[pair.first] << " --> " << pair.second << "\n\n";
		count++;
		if(count > numLines) break;
	}
	return 0;
}
