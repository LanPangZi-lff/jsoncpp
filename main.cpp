#include <iostream>
#include <json/json.h>
#include <string>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>

void writeFileFromString(const std::string& filename,const std::string& body)
{
    std::ofstream ofile(filename);
    ofile<<body;
    ofile.close();
}

std::string readFileIntoString(const char * filename)
{
    std::ifstream ifile(filename);
    if(!ifile.is_open()){
        std::cerr<<"文件打开错误";
    }
    std::ostringstream buf;
    std::string filestr;
    char ch;
    while(buf && ifile.get(ch)){
        buf.put(ch);
    }
    filestr = buf.str();
    return filestr;
}


Json::Value readJsonFile(const std::string & filename)
{
    //1.打开文件
    std::ifstream ifile;
    ifile.open(filename);
    
    //2.创建json读工厂对象
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8支持，不加这句，utf8的中文字符会编程\uxxx
    
    //3.创建json对象，等会要返回这个对象
    Json::Value root;
    
    //4.把文件转变为json对象，要用到上面的三个变量,数据写入root
    std::string strerr;
    bool ok = Json::parseFromStream(ReaderBuilder,ifile,&root,&strerr);
    if(!ok){
        std::cerr<<"json解析错误";
    }
    //5.返回存有数据的json，这个json对象已经能用了
    return root;
}

Json::Value readJsonFromString(const std::string& mystr )
{
    //1.创建工厂对象
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8支持,不加这句,utf8的中文字符会编程\uxxx
    //2.通过工厂对象创建 json阅读器对象
    std::unique_ptr<Json::CharReader> charread(ReaderBuilder.newCharReader());
    //3.创建json对象
    Json::Value root;
    //4.把字符串转变为json对象,数据写入root
    std::string strerr;
    bool isok = charread->parse(mystr.c_str(),mystr.c_str()+mystr.size(),&root,&strerr);
    if(!isok || strerr.size() != 0){
        std::cerr<<"json解析出错";
    }
    //5.返回有数据的json对象,这个json对象已经能用了
    return root;
}


void writeJsonFile(const std::string &filename,const Json::Value & root)
{
    //1.写json的工厂对象
    Json::StreamWriterBuilder writebuild;
    writebuild["emitUTF8"] = true;//utf8支持,加这句,utf8的中文字符会编程\uxxx
    //2.把json对象转变为字符串
    std::string document = Json::writeString(writebuild,root);
    //3.调用前面的写文件函数,写入文件
    writeFileFromString(filename,document);
}


int main(int, char**)
{
    //根节点  
	Json::Value root;
 
	//根节点属性  
	root["name"] = Json::Value("shuiyixin");
	root["age"] = Json::Value(21);
	root["sex"] = Json::Value("man");
 
	//子节点  
	Json::Value friends;
 
	//子节点属性  
	friends["friend_name"] = Json::Value("ZhaoWuxian");
	friends["friend_age"] = Json::Value(21);
	friends["friend_sex"] = Json::Value("man");
 
	//子节点挂到根节点上  
	root["friends"] = Json::Value(friends);
 
	//数组形式  
	root["hobby"].append("sing");
	root["hobby"].append("run");
	root["hobby"].append("Tai Chi");
    writeJsonFile("1.json",root);
    std::cout << "Hello, from demo!\n";

    Json::Value rotts;
    cv::Point3d p(0,0,0);
    rotts["points"][0].append((0,0,0));
    rotts["points"][1].append((8,9,10));
    rotts["points"][2].append((15,16,9));
    //1.写json的工厂对象
    Json::StreamWriterBuilder writebuild;
    writebuild["emitUTF8"] = true;//utf8支持,加这句,utf8的中文字符会编程\uxxx
    //2.把json对象转变为字符串
    std::string document = Json::writeString(writebuild,rotts);
    std::ofstream ofile("2.json");
    ofile<<document;
    ofile<<"gfdg";
    ofile.close();
}
