#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Director>& director) {

   if(operands.find("-name") != operands.end()){
        std::shared_ptr<Item> item = createItem(director->getCurrentSlide(), director->getCurrentSlideNumber());
        director->doAction(std::make_shared<AddItem>(item, director->getCurrentSlideNumber()));
        std::cout << "Added new item" << std::endl;
    }
    else if(operands.find("-slide") != operands.end()){
        director->doAction(std::make_shared<AddSlide>(std::make_shared<Slide>(), director->getCurrentSlideNumber() + 1));
        director->nextSlide();
        std::cout << "Added new slide" << std::endl;
    }

}

std::shared_ptr<Item> AddCommand::createItem(const std::shared_ptr<Slide>& slide, const size_t currentSlideIndex) {


    Type type = Type{Converter::convertToType(operands["-name"])};

    Position pos = Position{Converter::convertToPosition(operands["-pos"])};

    BoundingRect bounds = BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])};
    
    Color color; LineDescriptor lineDescriptor;
    if(operands.find("-lcolor") != operands.end()){
        color.hexLineColor = Converter::convertToColor(operands["-lcolor"][0]);
    }
    if (operands.find("-fcolor") != operands.end()){
        color.hexFillColor = Converter::convertToColor(operands["-fcolor"][0]);
    }
    if (operands.find("-lwidth") != operands.end()){
        lineDescriptor.width = std::stod(operands["-lwidth"][0]);
    }
    if (operands.find("-lstyle") != operands.end()){
        lineDescriptor.type = Converter::convertToLineType(operands["-lstyle"][0]);
    }


    return std::make_shared<Item>(type, pos, bounds, color, slide->generateID(), lineDescriptor);
;
}

void RemoveCommand::execute(std::shared_ptr<Director>& director) {
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> item = director->getCurrentSlide()->getItem(std::stoi(operands["-id"][0]));
        director->doAction(std::make_shared<RemoveItem>(item, director->getCurrentSlideNumber()));
    }
    else if(operands.find("-slide") != operands.end()){
        if(director->getDocument()->size() == 1){
            std::cout << "Cannot remove slide, only 1 left" << std::endl;
            
        } else {
            director->doAction(std::make_shared<RemoveSlide>(director->getCurrentSlide(), director->getCurrentSlideNumber())); // director has the slide it needs to remove
            director->previousSlide();
        }
        ////////////
    }

}


void ChangeCommand::execute(std::shared_ptr<Director>& director) {
    std::shared_ptr<Item> item = std::make_shared<Item>(*director->getCurrentSlide()->getItem(std::stoi(operands["-id"][0])));

    if(operands.find("-pos") != operands.end()){ 
        item->setPosition(Converter::convertToPosition(operands["-pos"]));
    }
    // if(operands.find("-name") != operands.end())
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        item->setBoundingRect(BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])}); 
    }
    if(operands.find("-lcolor") != operands.end()){
        item->setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        item->setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
    }
    if(operands.find("-lwidth") != operands.end()){
        item->setLineDescriptorWidth(std::stod(operands["-lwidth"][0]));
    }
    if(operands.find("-lstyle") != operands.end()){
        item->setLineDescriptorStyle(Converter::convertToLineType(operands["-lstyle"][0]));
    }

    director->doAction(std::make_shared<ChangeItem>(item, director->getCurrentSlideNumber()));
}


void SaveCommand::execute(std::shared_ptr<Director>& director) {  // review document versioning
    SaveLoadSerializer::save(director->getDocument(), operands["-path"][0] + operands["-name"][0]);

}

void LoadCommand::execute(std::shared_ptr<Director>& director) { 
    SaveLoadSerializer::load(operands["-path"][0]);
}

void DisplayCommand::execute(std::shared_ptr<Director>& director) {
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> item = director->getCurrentSlide()->getItem(std::stoi(operands["-id"][0]));
        Renderer renderer;
        renderer.renderText(std::cout, item);
    }
    else{
        Renderer renderer;
        renderer.renderText(std::cout, director->getCurrentSlide());
    }
}


void ListCommand::execute(std::shared_ptr<Director>& director) {
    Renderer renderer;
    renderer.renderText(std::cout, director->getDocument());
}

void NextCommand::execute(std::shared_ptr<Director>& director) {
    director->nextSlide();
}

void PrevCommand::execute(std::shared_ptr<Director>& director) {
    director->previousSlide();
}




void Command::addOperandToOperands(std::string operand) {
    operands[operand];                           // in case of no value
}

void Command::addValueToOperands(std::string value, std::string operand) {
    operands[operand].push_back(value);
}


std::string Command::getName() const {
    return name;
}

void Command::setName(std::string name) {
    this->name = name;
}

std::unordered_map<std::string, std::vector<std::string>> Command::getOperands() const {
    return operands;
}