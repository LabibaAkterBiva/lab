#include<iostream>
using namespace std;

class colour{

    public:
    virtual void colr ()const=0;
    virtual ~colour()=default;
};

class shape {
    public:
    virtual void shp()const=0;
    virtual ~shape()=default;

};
class Yellow:public colour{
  
    void colr() const{
        cout<<"Yello colour"<<endl;
    }
};
class rectangle:public shape{
 void shp()const{
    cout<<"rectangle shape"<<endl;
 }
};
class AbstractFactory {
    public:
        virtual shape* getShape(const string& shapeType) const = 0;
        virtual colour* getColour(const string& colourType) const = 0;
        virtual ~AbstractFactory() = default;
    };
    class ShapeFactory : public AbstractFactory {
        public:
            shape* getShape(const string& shapeType) const override {
                if (shapeType == "rectangle") {
                    return new rectangle();
                }
                return nullptr;
            }
        
            colour* getColour(const string& colourType) const override {
                return nullptr; // ShapeFactory doesn't create colours
            }
        };
        
        class ColourFactory : public AbstractFactory {
        public:
            shape* getShape(const string& shapeType) const override {
                return nullptr; // ColourFactory doesn't create shapes
            }
        
            colour* getColour(const string& colourType) const override {
                if (colourType == "yellow") {
                    return new Yellow();
                }
                return nullptr;
            }
        };
           
        class FactoryProducer {
            public:
                static AbstractFactory* getFactory(const string& type) {
                    if (type == "shape") {
                        return new ShapeFactory();
                    } else if (type == "colour") {
                        return new ColourFactory();
                    }
                    return nullptr;
                }
            };
            

            int main() {
                AbstractFactory* colourFactory = FactoryProducer::getFactory("colour");
                colour* yellow = colourFactory->getColour("yellow");
                if (yellow) yellow->colr();
            
                AbstractFactory* shapeFactory = FactoryProducer::getFactory("shape");
                shape* rect = shapeFactory->getShape("rectangle");
                if (rect) rect->shp();
            
                // Free memory
                delete yellow;
                delete rect;
                delete colourFactory;
                delete shapeFactory;
            
                return 0;
            }
            