#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct pupil{
    string name, surname, area;
    int index, year;
};

struct tabstud{
    int size = 0, cap = 2;
    pupil *ptable = new pupil[2];
};

void add(tabstud *ptab, pupil s){
    if(ptab->size == ptab->cap){
        ptab->cap = ptab->cap + 3;
        pupil *tmp = new pupil[ptab->cap];
        for (int i=0; i<ptab->size; ++i){
            *(tmp+i) = *(ptab->ptable + i);
        }
        delete[] ptab->ptable;
        ptab->ptable = tmp;
    }
    ptab->ptable[ptab->size] = s;
    ptab->size++;
}

void wipe_out(tabstud *ptab, int index){
    if(ptab->size==0){
        cout<<"The database is empty."<<endl;
    }else if (ptab->size==1){
        if(ptab->ptable[0].index==index){
            
            cout<<"Pupil " << ptab->ptable[0].name << "\t"
            << ptab->ptable[0].surname << "\t"
            << ptab->ptable[0].area << "\t"
            << ptab->ptable[0].year << "\t"
            << ptab->ptable[0].index << " has been wiped out" << "\n\n";

            pupil *tmp = new pupil[2];
            delete [] ptab->ptable;
            ptab->ptable=tmp;
            ptab->size--;
        }else{
            cout << "There is no pupil with such an index."<<endl;
        }
        
    }else{
        int present = 0;
        
        for(int i=0;i<ptab->size;i++){
            if(ptab->ptable[i].index==index){
                
                pupil *tmp = new pupil[ptab->size - 1];
                
                for(int i=0, j=0;i<ptab->size;i++){
                    if(ptab->ptable[i].index==index){
                        cout<<"Pupil " << ptab->ptable[i].name << "\t"
                        << ptab->ptable[i].surname << "\t"
                        << ptab->ptable[i].area << "\t"
                        << ptab->ptable[i].year << "\t"
                        << ptab->ptable[i].index << " has been wiped out" << "\n\n";
                        present++;
                    }else if(ptab->ptable[i].index!=index){
                        tmp[j] = ptab->ptable[i];
                        j++;
                    }
                }
                ptab->size--;
                delete [] ptab->ptable;
                ptab->ptable = tmp;
                
                break;
            }
        }
        if(!present){
            cout<<"There is no pupil with such an index."<<endl;
        }
        


    }
}

void replace(tabstud *ptab, int x, int y){
    pupil tmp = ptab->ptable[x];
    ptab->ptable[x] = ptab->ptable[y];
    ptab->ptable[y] = tmp;
}

void sort(tabstud *ptab, int start, int stop){
    int pivot;
    string name;
    if (start < stop){
        pivot = start;
        name = ptab->ptable[pivot].name;
        for (int i = start+1; i <= stop; ++i){
            if (ptab->ptable[i].name < name){
                pivot++;
                replace(ptab, pivot, i);
            }
        }
    replace(ptab, start, pivot);
    sort(ptab, start, pivot-1);
    sort(ptab, pivot+1, stop);
    }
}


int main(){
    
    tabstud pupils_diary;

    int answer;

    do{
        cout << "1 - add the pupil" << endl
        << "2 - search the pupil by index" << endl
        << "3 - display all pupils" << endl
        << "4 - remove the pupil with index" << endl
        << "5 - sort diary" << endl
        << "6 - save data of pupils" << endl
        << "7 - upload data of pupils from file"  << endl
        << "0 - finish" << endl;

        cin >> answer;

        if(answer == 1){
            
            pupil instance;

            cout << "name: ";
            cin >> instance.name;

            cout << "surname: ";
            cin >> instance.surname;

            cout << "area: ";
            cin >> instance.area;

            cout << "year: ";
            cin >> instance.year;

            cout << "index: ";
            cin >> instance.index;

            add(&pupils_diary, instance);

            cout << "Added: " << pupils_diary.ptable[pupils_diary.size-1].name << "\t"
            << pupils_diary.ptable[pupils_diary.size-1].surname << "\t"
            << pupils_diary.ptable[pupils_diary.size-1].area << "\t"
            << pupils_diary.ptable[pupils_diary.size-1].year << " year\t"
            << pupils_diary.ptable[pupils_diary.size-1].index << " index\n";
            

        }
        else if(answer == 2){

            int index;
            int present = 0;

            cout << "Pass index: ";
            cin >> index;

            for(int i = 0; i < pupils_diary.size; i++){
                if(pupils_diary.ptable[i].index == index){
                    cout << pupils_diary.ptable[i].name << "\t"
                    << pupils_diary.ptable[i].surname << "\t"
                    << pupils_diary.ptable[i].area << "\t"
                    << pupils_diary.ptable[i].year << "\t"
                    << pupils_diary.ptable[i].index << "\n\n";

                    present++;
                    break;
                }
            }
            
            if(!present){
                cout << "There is no pupil with such an index." << "\n\n";
            }

        }
        else if(answer == 3){

            for(int i = 0; i<pupils_diary.size; i++){
                cout << i+1 << " " << pupils_diary.ptable[i].name << "\t"
                << pupils_diary.ptable[i].surname << "\t"
                << pupils_diary.ptable[i].area << "\t"
                << pupils_diary.ptable[i].year << " year\t"
                << pupils_diary.ptable[i].index << " index\n";
            }

            cout << endl;

        }
        else if(answer == 4){
            
            int index, present;

            cout << "Pass index: ";
            cin >> index;

            wipe_out(&pupils_diary, index);
            
        }
        else if(answer == 5){
            if(pupils_diary.size > 1){
                sort(&pupils_diary, 0, pupils_diary.size - 1);
                cout<<"The diary is sorted."<< "\n\n";
            }else{
                cout<<"The database is too small or it's empty."<< "\n\n";
            }
            
        }
        else if(answer == 6){

            fstream file;
            string file_name;

            cout << "Enter the file name: ";
            cin >> file_name;

            file_name += ".txt";
            file.open( file_name, ios::out );

            if( !file.good() ){
                cout << "Save failed!\n";
            }else{
                cout << "Save completed!\n";
            }

            for(int i = 0; i < pupils_diary.size; i++){
                if(i == 0){
                    file << pupils_diary.ptable[i].name << "\t"
                    << pupils_diary.ptable[i].surname << "\t"
                    << pupils_diary.ptable[i].area << "\t"
                    << pupils_diary.ptable[i].year << "\t"
                    << pupils_diary.ptable[i].index;
                }else{
                    file << "\n" << pupils_diary.ptable[i].name << "\t"
                    << pupils_diary.ptable[i].surname << "\t"
                    << pupils_diary.ptable[i].area << "\t"
                    << pupils_diary.ptable[i].year << "\t"
                    << pupils_diary.ptable[i].index;
                }
                
                
            }

            file.close();

        }
        else if(answer == 7){

            fstream file;
            string file_name, linia, name, surname, area;
            int year, index, c = 0;
            
            cout << "Pass the file name: ";
            cin >> file_name;

            file_name;
            file.open( file_name, ios::in );
            
            if( !file.good() ){
                cout << "Upload failed!\n";
            }else{
                while(!file.eof()){
                    file >> name >> surname >> area >> year >> index;

                    pupil instance;                
                    instance.name = name;                
                    instance.surname = surname;                
                    instance.area = area;                
                    instance.year = year;                
                    instance.index = index;

                    add(&pupils_diary, instance);   
                }
                file.close();
            }
        }
    }while(answer != 0);
    
    return 0;  
}