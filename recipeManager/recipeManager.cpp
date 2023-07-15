#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

struct User 
{
    string username;
    string password;
};

struct Recipe 
{
    string name;
    string ingredients;
    string instructions;
};

Recipe recipesFromFile[50];
int size = 0;

void clrscr()
{
    system("cls");
}

void printProjectTitle()
{
    string projectName = "\033[3mRECIPE MANAGER\033[0m";
    string line(50, '-');

    cout << line << endl;
    cout << "\t\t" << projectName << endl;
    cout << line << endl;

}

void addRecipe()
{
    Recipe newRecipe;
    bool recipeExists = false;
    cout << "Enter name of the recipe: ";
    getline(cin, newRecipe.name);

    cout<<"Enter ingredients one by one: "<<endl;
    string s;
    while(true)
    {
        getline(cin, s);
        if(s == "q")
            break;

        s = "- " + s + "\n";
        newRecipe.ingredients += s;
    }
 
    cout << "Entered Ingredients: " << endl;
    cout << newRecipe.ingredients << endl;

    cout << "Enter instructions of the recipe: " << endl;
    string i;
    int n = 0;

    while(true)
    {
        getline(cin, i);
        if(i == "q")
            break;

        n++;
        string num = to_string(n);
        i = num + ". " + i + "\n";
        newRecipe.instructions += i;
    }

    cout << "Entered Instructions: " << endl;
    cout << newRecipe.instructions << endl;

    ofstream recipeFile("recipes.txt", ios::app);
    recipeFile << "Recipe: " << newRecipe.name << endl;
    recipeFile << "--------------------------------------------------" << endl;
    recipeFile << "Ingredients:" << endl;
    recipeFile << newRecipe.ingredients << endl;
    recipeFile << "Instructions:" << endl;
    recipeFile << newRecipe.instructions;
    recipeFile << "==================================================" << endl;

    recipeFile.close();

    cout << "Recipe added successfully!" << endl;
}

void getRecipesFromFile()
{
    ifstream inputFile("recipes.txt");
    if (!inputFile)
    {
        cout << "Error opening file." << endl;
    }

    string line;
    int num = 1;
    int count = 0;
    while (getline(inputFile, line))
    {
        string i = to_string(num);
        
        if (line == "==================================================")
        {   
            count++;
            num = 1;
        }
        else if (line[0] == 'R')
        {
            recipesFromFile[count].name = line;
        }
        else if (line[0] == '-' && line[1] == ' ')
        {
            recipesFromFile[count].ingredients += line + "\n";
        }
        else if (line[0] == i[0] && line[1] == '.')
        {
            recipesFromFile[count].instructions += line + "\n";
            num++;
        }   
    }

    // printing for testing 
    // for(int i=0; i<=count; i++)
    // {
    //     cout<< recipesFromFile[i].name << endl;
    //     cout<< recipesFromFile[i].ingredients << endl;
    //     cout<< recipesFromFile[i].instructions << endl;
    // }

    inputFile.close();
    size = count-1;
}

void saveRecipesToFile()
{
    ofstream recipeFile("recipes.txt");
    for(int i=0; i<=size; i++)
    {
        recipeFile << recipesFromFile[i].name << endl;
        recipeFile << "--------------------------------------------------" << endl;
        recipeFile << "Ingredients:" << endl;
        recipeFile << recipesFromFile[i].ingredients << endl;
        recipeFile << "Instructions:" << endl;
        recipeFile << recipesFromFile[i].instructions;
        recipeFile << "==================================================" << endl;
    }
    recipeFile.close();
}

void editRecipe()
{
    getRecipesFromFile();
    for(int i=0; i<=size; i++)
    {
        cout<< i+1 << ". " << recipesFromFile[i].name << endl;
    }

    cout<<"\nSelect recipe you want to edit: ";
    int n;
    cin>>n;

    cout<< recipesFromFile[n-1].name << endl;
    cout<< "--------------------------------------------------" << endl;
    cout<< "Ingredients:" << endl;
    cout<< recipesFromFile[n-1].ingredients << endl;
    cout<< "Instructions:" << endl;
    cout<< recipesFromFile[n-1].instructions << endl;
    cout<< "==================================================" << endl;
    
    char ans;
    cout << "Do you want to edit name?(y/n) ";
    cin >> ans;
    cin.ignore();

    if(ans == 'y')
    {
        cout << "Enter new name of the recipe: ";
        getline(cin, recipesFromFile[n-1].name);
        recipesFromFile[n-1].name = "Recipe: " + recipesFromFile[n-1].name;
    }
    
    cout << "Do you want to edit ingredients?(y/n) ";
    cin >> ans;
    cin.ignore();
    
    if(ans == 'y')
    {
        recipesFromFile[n-1].ingredients = "";
        cout<<"Enter new ingredients one by one: "<<endl;
        string s;
        while(true)
        {
            getline(cin, s);
            if(s == "q")
                break;

            s = "- " + s + "\n";
            recipesFromFile[n-1].ingredients += s;
        }
    }
    
    cout << "Do you want to edit instructions?(y/n) ";
    cin >> ans;
    cin.ignore();

    if(ans == 'y')
    {
        recipesFromFile[n-1].instructions = "";
        cout << "Enter new instructions of the recipe: " << endl;
        string ins;
        int c = 0;

        while(true)
        {
            getline(cin, ins);
            if(ins == "q")
                break;

            c++;
            string num = to_string(c);
            ins = num + ". " + ins + "\n";
            recipesFromFile[n-1].instructions += ins;
        }
    }

    cout<< recipesFromFile[n-1].name << endl;
    cout<< "--------------------------------------------------" << endl;
    cout<< "Ingredients:" << endl;
    cout<< recipesFromFile[n-1].ingredients << endl;
    cout<< "Instructions:" << endl;
    cout<< recipesFromFile[n-1].instructions << endl;
    cout<< "==================================================" << endl;

    saveRecipesToFile();
}

void displayRecipe()
{
    getRecipesFromFile();
    for(int i=0; i<=size; i++)
    {
        cout<< i+1 << ". " << recipesFromFile[i].name << endl;
    }

    cout<<"\nEnter recipe number to display: ";
    int n;
    cin>>n;

    cout<< recipesFromFile[n-1].name << endl;
    cout<< "--------------------------------------------------" << endl;
    cout<< "Ingredients:" << endl;
    cout<< recipesFromFile[n-1].ingredients << endl;
    cout<< "Instructions:" << endl;
    cout<< recipesFromFile[n-1].instructions << endl;
    cout<< "==================================================" << endl;
}

void searchRecipe()
{
    getRecipesFromFile();

    string s;
    cout<< "\nSearch recipe name: ";
    getline(cin, s);

    int i;
    s = "Recipe: " + s;

    for (i = 0; i <= size; i++)
    {
        if (recipesFromFile[i].name == s)
        {
            break;
        }
    }

    if (i <= size)
    {
        cout << recipesFromFile[i].name << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Ingredients:" << endl;
        cout << recipesFromFile[i].ingredients << endl;
        cout << "Instructions:" << endl;
        cout << recipesFromFile[i].instructions << endl;
        cout << "==================================================" << endl;
    }
    else
    {
        cout << "Recipe not found!" << endl;
    }
}

void mainMenu()
{
    clrscr();
    int choice;

    printProjectTitle();
    cout << "1. Add Recipe" << endl;
    cout << "2. Edit Recipe" << endl;
    cout << "3. Display Recipe" << endl;
    cout << "4. Search Recipe" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    clrscr();

    switch (choice)
    {
        case 1:
            addRecipe();
            break;
        case 2:
            editRecipe();
            break;
        case 3:
            displayRecipe();
            break;
        case 4:
            searchRecipe();
            break;
        case 5:
            cout << "Exiting program!" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }

    cout << endl;

}

void loginUser()
{
    User currentUser, fileUser;
    bool userExists = false;
    cout << "Login to an existing account!" << endl;
    cout << "Enter username: ";
    cin >> currentUser.username;
    cout << "Enter password: ";
    cin >> currentUser.password;

    ifstream myFile("users.txt");
    
    while(myFile >> fileUser.username >> fileUser.password)
    {
        if(currentUser.username == fileUser.username && currentUser.password == fileUser.password)
        {
            cout << "Login successful!" << endl;
            userExists = true;
            break;
        }
    }

    if(!userExists)
    cout << "User does not exist. Please register first!" << endl;
    else
        mainMenu();
    
    myFile.close();
 }

void registerUser()
{
    User newUser, registeredUser;
    bool usernameExists = false;
    cout << "Don't have an account? Sign up!" << endl;
    cout << "Enter username: ";
    cin >> newUser.username;
    cout << "Enter password: ";
    cin >> newUser.password;

    ifstream userFile("users.txt");
    while (userFile >> registeredUser.username >> registeredUser.password)
    {
        if(newUser.username == registeredUser.username)
        {
            cout << "Username not available! Please enter a new one." << endl;
            usernameExists = true;
            break;
        }
    }

    userFile.close();

    if(!usernameExists)
    {
        ofstream userFile("users.txt", ios::app);
        userFile << newUser.username << " " << newUser.password << endl;
        cout << "Registration successful!" << endl;
        userFile.close();
        clrscr();
        loginUser();
    }
}

int main()
{
    printProjectTitle();

    int choice;
    cout << "\n\nTo start, first you have to Login to your account." << endl;
    cout << "If you don't have an account, then register yourself first!" << endl;
    cout << "\n1. LOGIN\n2. REGISTRATION\n3. EXIT" << endl;
    cout << "\nEnter your choice >> ";
    cin >> choice;
    cin.ignore();

    switch(choice) 
    {
    case 1:
        clrscr();
        loginUser();
        break;
    case 2:
        clrscr();
        registerUser();
        break;
    case 3:
        cout << "Exiting program!" << endl;
        break;
    default:
       cout << "Invalid choice." << endl;
    }

}