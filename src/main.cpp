#include "Classifier.h"

#define CPU_ONLY 1
//#define Folder_file 1
#define Txt_file 1

int main(int argc, char** argv) {

    ::google::InitGoogleLogging(argv[0]);

//    string model_file   = "./alphanumeric/imagenet_deploy.prototxt";
//    string trained_file = "./alphanumeric/caffenet_train_iter_4680.caffemodel";
//    string mean_file    = "./alphanumeric/imagenet_mean.binaryproto";
//    string label_file   = "./alphanumeric/label.txt";

    string model_file   = "./400classes/imagenet_deploy.prototxt";
    string trained_file = "./400classes/caffenet_train_iter_500.caffemodel";
    string mean_file    = "./400classes/imagenet_mean.binaryproto";
    string label_file   = "./400classes/label.txt";

//    string model_file   = "./400classes/googlenet_deploy.prototxt";
//    string trained_file = "./400classes/Googlenet_train_iter_38000.caffemodel";
//    string mean_file    = "./400classes/googlenet_mean.binaryproto";
//    string label_file   = "./400classes/label.txt";

    Classifier classifier(model_file, trained_file, mean_file, label_file);

    string test_file_path = "./new";
    int classes = 10;   //total classes
    float count = 0;  	//for accuracy
    float TotalNumberOfTestImages = 0;
    struct timeval tpstart,tpend;
    float timeuse;
    gettimeofday(&tpstart,NULL);

    ofstream result;
    result.open("Result.txt",ios::out);

  #ifdef Folder_file
    //read file from FOLDERS
    for (int current_class = 0; current_class < classes ; current_class++){
        for (int filename = 1;filename <= 10; filename++){
            ++TotalNumberOfTestImages;
            stringstream sstr;
            sstr << test_file_path << "/" << current_class << "/" << filename << ".jpg";
//             sstr << test_file_path << "/" << filename << ".jpg";
            string file = sstr.str();
     //read file from FOLDERS
  #endif

  #ifdef Txt_file
      //read file form TXT
      ifstream testFile("./400classes/Test.txt");
      string strtmp;
      vector<string> vect,vect_class;
      while(getline(testFile, strtmp, '\n')){
          vect.push_back(strtmp.substr(0, strtmp.find(' ')));
          vect_class.push_back(strtmp.substr(strtmp.find(' '),strtmp.size()));
      }
      for(int j = 0; j < vect.size(); j++){
          string file = vect[j];
          string Cuclass = vect_class[j];
          TotalNumberOfTestImages = vect.size();
      //read file form TXT
  #endif

          std::cout << "------ Prediction for " << file << " ------" << std::endl;
          cv::Mat img = cv::imread(file, -1);
          CHECK(!img.empty()) << "Unable to decode image " << file;

          std::vector<Prediction> predictions = classifier.Classify(img,1);//return top1 prediction


          /* Print the top N predictions. */
          for (size_t i = 0; i < predictions.size(); ++i) {
              Prediction p = predictions[i];
            std::cout << std::fixed << std::setprecision(4) << p.second << " - \""
                      << p.first << "\"" << std::endl;
//              result << std::fixed << std::setprecision(4) << p.second << " - \""
//                     << p.first  << std::endl;

              //string to number
              int predicted_class;
              stringstream convert(p.first);
              convert >> predicted_class;


  #ifdef Txt_file
              int current_class;
              stringstream convert1(Cuclass);
              convert1 >> current_class;
              cout << count+1 << "\t" << j+1 << endl;
  #endif

              if(predicted_class == current_class)
                  count++;
          }
      }
      cout << "count : " << count << "\t" "Numbers: " << TotalNumberOfTestImages << endl;

#ifdef Folder_file
    }
#endif

#ifdef Txt_file
      testFile.close();
#endif
      result.close();
      gettimeofday(&tpend,NULL);
      timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
      timeuse /= 1000000;
      std::cout << "Accuracy: " << count << "/" << TotalNumberOfTestImages
                << " = " << count/TotalNumberOfTestImages
                << "\nTime used: " << timeuse << " seconds." << std::endl;

}

