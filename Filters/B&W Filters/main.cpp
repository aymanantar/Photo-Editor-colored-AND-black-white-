//heyy
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];

void convertBlackWhilte() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }
}

void InvertImage () {

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }

}

void mergeImages () {

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image3[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }

}

void FlipImage () {

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = image[255-i][255-j];
        }
    }
    cout<<"\n";
}

void rotateImage () {

    while (true) {
        string rotate;
        cout << "enter the degree ( 90, 180, 270 ) you want to rotate your image : ";
        cin >> rotate;
        cout << "\n";

        if (rotate == "90") {
            for (int i = 0, k = SIZE - 1; i < SIZE; ++i, k--) {
                for (int j = 0, l = 0; j < SIZE; ++j, ++l) {
                    image2[l][k] = image[i][j];
                }
            }
            break;
        }

        else if (rotate == "180") {
            for (int i = 0, k = SIZE - 1; i < SIZE; ++i, k--) {
                for (int j = 0, l = SIZE - 1; j < SIZE; ++j, --l) {
                    image2[k][l] = image[i][j];
                }
            }
            break;
        }

        else if (rotate == "270") {
            for (int i = 0, k = SIZE - 1; i < SIZE; ++i, k++) {
                for (int j = 0, l = SIZE - 1; j < SIZE; ++j, --l) {
                    image2[l][k] = image[i][j];
                }
            }
            break;
        }

        else {
            cout << "sorry we can not rotate it to this degree, try again.\n";
            rotate = "";
        }
    }


}

void darkenLighten () {

    string choice;
    cout<<"choose which operation you want to do\n"
          "1- darken \n"
          "2- lighten\n";

    cout<<"enter your choice : ";
    cin>>choice;

    if (choice == "1") {

        for (int i = 0; i < SIZE; ++i) {

            for (int j = 0; j < SIZE; ++j) {
                image[i][j] -= image[i][j]/2;
                if (image[i][j] < 0 ) image[i][j] = 0;

            }
        }
    }

    if (choice == "2") {

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                image[i][j] = (image[i][j] + 256) / 2;

            }
        }
    }


}

void detectEdges() {
 cout<<"choose the sharpness degree of edges in range 1-9 \n 1 too soft , 9 too sharp\n";
 int deg; cin>>deg; deg*=50;
 int filv[3][3]= {{1,2,1},{0,0,0}, {-1,-2,-1} };
  int filh[3][3]= {{-1,0,1},{-2,0,2}, {-1,0,1} };
  for (int i = 0; i < SIZE; i++) {
     for (int j =0 ; j< SIZE; j++) {
      int sumv=0,sumh=0,sum=0;
      int a=0,b=0;

    if ( !( i==0 || j==0||i==SIZE-1 || j==SIZE-1  )  )  {
    for (int k =-1 ; k<2 ; k++){
        for (int l=-1; l<2; l++){
        sumh +=  (filh[l+1][k+1]) * (image[i+l][j+k]) ;
        sumv +=  (filv[k+1][l+1]) * (image[i+k][j+l]) ;
        }
     }

       if ( sqrt(pow(sumh,2)+pow(sumv,2)) > (650-deg)){
        image2[i][j]=0;
       }
       else{
        image2[i][j]=255;
       }
    }
    else {
        image2[i][j]=255;
    }
    }

  }

}


void EnlargeImage () {

    while (true) {
        string quarter ;
        cout<<"enter the quarter you want to enlarge : ";
        cin>>quarter;

        if (quarter == "1"){

            for (int i = 0, k = 0; i < SIZE ; i+=2,++k) {
                for (int j = 0, l = 0; j < SIZE/2; ++j,++l) {
//                  in this loop we take each pixel in the original image and put it twice in the enlarged image

                    image2[i][l+j] = image[k][j];
                    image2[i][l+j+1] = image[k][j];

                }
//                 in this loop we copy the first row and paste it in the second row and so on.
                for (int j = 0; j < SIZE; ++j) {
                    image2[i+1][j] = image2[i][j];
                }
            }
            break;
        }

        else if (quarter == "2") {
            for (int i = 0 , k = 0; i < SIZE; i+=2,++k) {
                for (int j = SIZE/2 , l = 0; j < SIZE ; ++j,l++) {
                    image2[i][l+j-128] = image[k][j];
                    image2[i][l+1+j-128] = image[k][j];
                }
                for (int j = 0; j < SIZE; ++j) {
                    image2[i+1][j] = image2[i][j];
                }
            }
            break;
        }

        else if (quarter == "3") {

            for (int i = 0 , k = SIZE/2 ; i < SIZE; i+=2,k++) {
                for (int j = 0 ,l = 0; j < SIZE/2; ++j,l++) {
                    image2[i][l+j] = image[k][j];
                    image2[i][l+j+1] = image[k][j];
                }
                for (int j = 0; j < SIZE; ++j) {
                    image2[i+1][j] = image2[i][j];
                }
            }
            break;
        }

        else if (quarter == "4") {
            for (int i = 0 , k = SIZE/2; i < SIZE; i+=2 , ++k) {

                for (int j = SIZE/2 , l = 0; j < SIZE; ++j,++l) {

                    image2[i][l+j-128] = image[k][j];
                    image2[i][l+j-128+1] = image[k][j];

                }

                for (int j = 0; j < SIZE; ++j) {
                    image2[i+1][j] = image2[i][j];
                }
            }
            break;
        }
        else {
            cout<<"there is only 4 quarters,you can choose one of them, try again.\n";
            quarter = "";
        }

    }

}

void mirrorImage () {

    while (true) {
        string half ;
        cout<<"choose which half you want to mirror\n"
              "1- choose 1 to mirror the upper half.\n"
              "2- choose 2 to mirror the lower half.\n"
              "3- choose 3 to mirror the left half.\n"
              "4- choose 4 to mirror the right half.\n";
        cout<<"make your choice : ";
        cin>>half;

        if (half == "1") {

            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[255-i][j] = image[i][j];
                }
            }
            break;
        }

        else if (half == "2") {
            for (int i = 0; i < SIZE/2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[i][j] = image[255-i][j];
                }
            }
            break;
        }

        else if (half == "3") {

            for (int i = 0; i < SIZE/2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[j][255-i] = image[j][i];
                }
            }
            break;
        }

        else if (half == "4"){
            for (int i = 0; i < SIZE/2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[j][i] = image[j][255-i];
                }
            }
            break;
        }

        else {
            cout<<"your choice has to be from 1 to 4, you cannot choose "<<half<<"\n";
            half = "";
        }
    }
}

void shuffleImage () {
int arr [4];
cout<<"enter your shuffle order -space separated- \n";
while (true){
    string s;
    int a=0;
    bool flag=1;
    cin.clear(); cin.sync();getline(cin,s);
    for (int i=0; i<7 ; i++)  {
    if (s[i]==' '){a++;continue;}
    if (s[i]=='1'||s[i]=='2'||s[i]=='3'||s[i]=='4'){
        arr[i-a]=s[i]-'0';
    }
    else {
            cout<<"please enter a valid input only include numbers in range 1-4 -space separated-  \n";
            flag=0;
            break;
    }
            }
        if (flag) break;
    }
    for (int i =0 ; i< 256;i++ ){
        for (int j=0 ; j<256;j++){
            image2[i][j]=image[ ( ((arr[ 2*(i/128) + (j/128)]+1)/4)*128 )+ (i%128) ][ (  (  ((arr[ 2*(i/128) + (j/128)]%2)+3)  %2)*128 )+ (j%128) ];
        }
    }

}


void blurImage () {
  cout<<"how do you like to make a blur\n 1-average blur \n 2-normal distribution optimized blur\n";
  int t; cin>>t;
  if ( t==2){
  int d=0;int n=0;
  cout<<"chose the degree of blur (must be odd number in range 3-9 ) \n";
  while (1){
  string s; cin>>s;
  n=s[0]-'0';
  if (n%2==1 && n<=9 &&n>=3 ){break;}
  cout<<"not an odd number or not in range 3-9, please try another time with valid number\n";
  }
  int fil[n][n];
  fil[n/2][n/2]= pow(2,n-1) ;
  d=fil[n/2][n/2];
  for (int i=1 ; i<=n/2; i++){fil[n/2][(n/2)-i]=(fil[n/2][(n/2)-i+1])/2 ;
   d+=fil[n/2][(n/2)-i];
     fil[n/2][(n/2)+i]=(fil[n/2][(n/2)+i-1])/2;
     d+= fil[n/2][(n/2)+i];}
  for (int i=0 ; i<n; i++){
    for (int j=1;j<=n/2;j++){fil[(n/2)-j][i]=(fil[(n/2)-j+1][i])/2 ; d+=fil[(n/2)-j][i];fil[(n/2)+j][i]=(fil[(n/2)+j-1][i])/2;  d+=fil[(n/2)+j][i];}
  }
  for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j< SIZE; j++) {
      int sumv=0,sumh=0,sum=0;
    if (i>=SIZE-(n/2) && j>=SIZE-(n/2)){
            for (int k =0 ; k<n-(i-(SIZE-(n/2))); k++){
        for (int l=0; l<n-(j-(SIZE-(n/2))); l++){
        sum +=  (image[i+k][j+l]) * (fil[k][l]) ;
        }
     }
    }
    else if (i>=SIZE-(n/2)){
            for (int k =0 ; k<n-(i-(SIZE-(n/2))); k++){
        for (int l=0; l<n; l++){
        sum +=  (image[i+k][j+l]) * (fil[k][l]) ;
        }
     }
    }
    else if (j>=SIZE-(n/2)){
            for (int k =0 ; k<n; k++){
        for (int l=0; l<(n-(j-(SIZE-(n/2)))); l++){
        sum +=  (image[i+k][j+l]) * (fil[k][l]) ;
        }
     }
    }
    else {
    for (int k =0 ; k<n; k++){
        for (int l=0; l<n; l++){
        sum +=  (image[i+k][j+l]) * (fil[k][l]) ;
        }
     }
    }
        image2[i][j]=sum/d;
    }

  }

}

else if (t==1){
      int d=0;

  cout<<"chose the degree of blur \n ";
  int n; cin>>n;
  for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j< SIZE; j++) {
      int sum=0,d=0;;
            if (i>=SIZE-(n/2) && j>=SIZE-(n/2)){
    for (int k =0 ; k<(n-(i-(SIZE-(n/2)))); k++){
        for (int l=0; l<(n-(j-(SIZE-(n/2)))); l++){
          sum +=  (image[i+k][j+l])  ; d++;
        }
     }
      }
      else if (i>=SIZE-(n/2)){
    for (int k =0 ; k<(n-(i-(SIZE-(n/2)))); k++){
        for (int l=0; l<n; l++){
          sum +=  (image[i+k][j+l])  ; d++;
        }
     }
      }
            else if (j>=SIZE-(n/2)){
    for (int k =0 ; k<n; k++){
        for (int l=0; l<(n-(j-(SIZE-(n/2)))); l++){
          sum +=  (image[i+k][j+l])  ; d++;
        }
     }

      }
      else{
    for (int k =0 ; k<n; k++){
        for (int l=0; l<n; l++){
           sum +=  (image[i+k][j+l])  ;
        }
     }


    }
        if (!d)image2[i][j]=sum/pow(n,2);
        else image2[i][j]=sum/d;

  }


}
}

}



void loadImage () {

    char imageName[100];

    cout << "Enter the source image file name: ";
    cin >> imageName;

    strcat (imageName, ".bmp");
    readGSBMP(imageName, image);

    cout<<"\n";
}

void loadImage2 () {

    char imageName[100];

    cout << "Enter the source image 2 file name: ";
    cin >> imageName;

    strcat (imageName, ".bmp");
    readGSBMP(imageName, image2);

    cout<<"\n";
}


void saveImage () {

    char imageName[100];

    cout << "Enter the target image file name: ";
    cin >> imageName;

    strcat (imageName, ".bmp");
    writeGSBMP(imageName, image);

    cout<<"\n";
}

void saveImage2 () {

    char imageName[100];

    cout << "Enter the target image file name: ";
    cin >> imageName;

    strcat (imageName, ".bmp");
    writeGSBMP(imageName, image2);

    cout<<"\n";
}

void saveImage3 () {

    char imageName[100];

    cout << "Enter the target image file name: ";
    cin >> imageName;

    strcat (imageName, ".bmp");
    writeGSBMP(imageName, image3);

    cout<<"\n";
}

int main()
{
    while (true) {
        string choice ;
 cout << "please select a filter to be applied \n"
                "1- black and white filter\n"
                "2- invert filter\n"
                "3- merge filter\n"
                "4- flip image\n"
                "5- lighten and darken image\n"
                "6- rotate image\n"
                "7- detect edges\n"
                "8- enlarge image\n"
                "a- mirror image\n"
                "b- shuffle image\n"
                "c- blur image\n"
                "0- exit\n";
        cin>>choice;
        if (choice =="0") break;

        if (choice == "1") {
            loadImage();
            convertBlackWhilte();
            saveImage();

        }

        else if (choice == "2") {
            loadImage();
            InvertImage();
            saveImage();

        }

        else if (choice == "3") {
            loadImage();
            loadImage2();
            mergeImages();
            saveImage3();


        }

        else if (choice == "4") {
            loadImage();
            FlipImage();
            saveImage2();

        }

        else if (choice == "5") {
            loadImage();
            rotateImage();
            saveImage2();

        }

        else if (choice == "6") {
            loadImage();
            darkenLighten();
            saveImage();

        }

        else if (choice == "7"){ //done
            loadImage();
            detectEdges();
            saveImage2();
        }

        else if (choice == "8"){
            loadImage();
            EnlargeImage();
            saveImage2();

        }

        else if (choice == "a") {
            loadImage();
            mirrorImage();
            saveImage();

        }

        else if (choice == "b") {
            loadImage();
            shuffleImage();
            saveImage2();
        }

        else if (choice == "c") {
            loadImage();
            blurImage();
            saveImage2();
        }

        else if (choice == "0") {
            cout<<"good bye \n";
            break;
        }
    }



    return 0;
}
