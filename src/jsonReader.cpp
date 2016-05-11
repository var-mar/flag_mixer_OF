#include "jsonReader.h"

jsonReader::jsonReader() {}

vector<flag> jsonReader::getData() {
	clearData();
	if (setCountryData()) setFlags();
	return flags;
}

bool jsonReader::openFile(ofxJSONElement& _file, string _name, string _path) {
	if (_file.open(_path+_name)) {
		cout << "File "+ _name +" opened" << endl;
		return true;
	}
	else {
		cout << "Error while opening file "+ _name << endl;
		return false;
	}
}

bool jsonReader::setCountryData() {
	if (openFile(countriesFile, COUNTRIES_FILE, FILE_PATH)) {
		std::size_t numCountries = countriesFile.size();
		if (COUNTRIES_TO_READ < numCountries) {
			for (Json::ArrayIndex i = 0; i < COUNTRIES_TO_READ; ++i) {
				country country;
				country.name = countriesFile[i]["code"].asString();
				country.count = countriesFile[i]["count"].asInt();
				countryData.push_back(country);
			}
			return true;
		}
		else {
			cout << "Not enought countries to read" << endl;
		}
	}
	return false;
}

void jsonReader::setFlags() {
	for (int i = 0; i < countryData.size(); i++) {
		flags.push_back(createFlag(countryData[i]));
	}
}


flag jsonReader::createFlag(country _country) {
	flag flag;
	if (openFile(flagsFile, FLAGS_FILE, FILE_PATH)) {
		if (flagsFile.isMember(_country.name)) {
			flagBackground bg;
			vector<flagLayer> layers;
			bg = loadFlagBackground(_country);
			if (flagsFile[_country.name].isMember("layer")) {
				std::size_t numLayers = flagsFile[_country.name]["layer"].size();
				for (Json::ArrayIndex i = 0; i < numLayers; ++i) {
					layers.push_back(loadFlagLayer(_country, i));
				}
			}
			flag.setup(bg,layers,_country.name,_country.count);
		}
		else {
			cout << "Country " + _country.name + " not found" << endl;
		}
	}
	return flag;
}

flagObject jsonReader::loadFlagObject(country _country, int _index) {
	flagObject ob;
	Json::Value context = _index != -1 ? flagsFile[_country.name]["layer"][_index] : flagsFile[_country.name]["background"];
	if (context.isMember("colors")) {
		std::size_t num = context["colors"].size();
		for (Json::ArrayIndex i = 0; i < num; ++i) {
			ob.colors.push_back(getColorFromInt(context["colors"][i].asInt()));
		}
	}
	if (context.isMember("strokeColor"))ob.strokeColor = getColorFromInt(context["strokeColor"].asInt());
	if (context.isMember("strokeWeight"))ob.strokeWeight = context["strokeWeight"].asInt();
	if (context.isMember("type"))ob.type = context["type"].asInt();

	return ob;
}

flagBackground jsonReader::loadFlagBackground(country _country) {
	flagBackground fB;
	Json::Value context = flagsFile[_country.name]["background"];
	fB.object = loadFlagObject(_country);
	if (context.isMember("symmetry")) {
		std::size_t num = context["symmetry"].size();
		for (Json::ArrayIndex i = 0; i < num; ++i) {
			fB.symmetry.push_back(context["symmetry"][i].asInt());
		}
	}

	return fB;
}

flagLayer jsonReader::loadFlagLayer(country _country, int _index) {
	flagLayer fL;
	Json::Value context = flagsFile[_country.name]["layer"][_index];
	fL.object = loadFlagObject(_country, _index);
	if (context.isMember("center")) {
		std::size_t num = context["center"].size();
		if (num == 2) {
			fL.center.x = context["center"][0].asInt();
			fL.center.y = context["center"][1].asInt();
		}
	}
	if (context.isMember("angle"))fL.angle = context["angle"].asInt();
	if (context.isMember("height"))fL.height = context["height"].asInt();
	if (context.isMember("scale"))fL.scale = context["scale"].asInt();

	return fL;
}

ofColor jsonReader::getColorFromInt(int _int) {
	return ofColor::fromHex(_int);
}

void jsonReader::clearData() {
	countryData.clear();
	flags.clear();
}