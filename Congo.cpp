#include<iostream>
#include<map>
#include<ctype.h>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<fstream>

using namespace std;

fstream file;


//sort the pieces positions
map<char,string> Sort(map<char,string> pieces){
    vector<string> vec;
    string fin;
    
    for(auto entry : pieces){

        string x = entry.second;
        string result = "";

        if(x.length()!=2){

            for(int i = 0 ; i < x.length()-1 ; i+=3){
                result += x[i];
                result += x[i+1];
                vec.push_back(result);
                result = "";
            }

            sort(vec.begin() , vec.end());

            for(int i = 0 ; i < vec.size() ; i ++){
                if(i==0){
                    fin += vec[i];
                }
                else{
                    fin+= " "+ vec[i];
                }
            }
            pieces[entry.first] = fin;
            fin = "";
            vec.clear();
        }
        
    }
    return pieces;
}


map<char,string> GetPositions(string fen){

    map<char,string> pieces;

    int i = 0;
    char count = 'a';
    int rank = 7;
    char sidetoplay;
    string N;

    //The Ranks
    for(i ; i < fen.length() ; i ++){
 
        if(fen[i] == ' '){
            break;
        }
        
        //digit
        if(!isalpha(fen[i]) && fen[i] != '/'){
            count += (fen[i]-'0');
        }
        //decrement rank
        else if(fen[i] == '/'){
            rank--;
            count = 'a';
        }
        
        //its a piece
        else{
            string res = count + to_string(rank);
            //remove extra spacing
            if(pieces.count(fen[i])){
                pieces[fen[i]] += " "+ res;
                
            }
            else{
                pieces[fen[i]] +=  res;
            }
            
            count++;
        }
         
    }

    //The Last bit of info
    for(i+1 ; i < fen.length() ; i ++ ){
        
        if(fen[i] != ' '){

            if(isalpha(fen[i])){
                sidetoplay = fen[i];
            }
            else{
                N += fen[i];
            }
        }
    }

    pieces = Sort(pieces);
    //x side to play(b|w)
    //y total moves 
    pieces['x'] = sidetoplay;
    pieces['y'] = N;

    return pieces;
}


vector<vector<char> > GenBoard(map<char,string> Locations){
    
    vector<vector<char> > Board(7 , vector<char>(7 , '0'));

 
   //fill the board at that position
    for(auto  entry : Locations){

        if(entry.first != 'x' && entry.first != 'y'){

            for(int i = 0 ; i < entry.second.length() ; i +=3){
                
                int col =  entry.second[i] - 'a';
                int row = entry.second[i+1] - '0';
                
                Board[row-1][col] = entry.first;

            }
        }
    }
    return Board;
    
}


void PrintPositions(map<char,string> pieces){
    
    char Piece[16] = {'P' , 'p' , 'S' , 's' , 'G' , 'g' , 'M' , 'm' , 'E' , 'e' , 'L' , 'l' , 'C' , 'c' , 'Z' , 'z'};
    bool white = false;
    bool black = false;
    string Animal;

    for(int i = 0 ; i < 15 ; i+=2){

        white = pieces.find(Piece[i]) != pieces.end();
        black = pieces.find(Piece[i+1]) != pieces.end();

        if(Piece[i] == 'P'){
            Animal = "pawn:";
        }
        else if(Piece[i] == 'S'){
            Animal = "superpawn:";
        }
        else if(Piece[i] == 'G'){
            Animal = "giraffe:";
        }
        else if(Piece[i] == 'M'){
            Animal = "monkey:";
        }
        else if(Piece[i] == 'E'){
            Animal = "elephant:";
        }
        else if(Piece[i] == 'L'){
            Animal = "lion:";
        }
        else if(Piece[i] == 'C'){
            Animal = "crocodile:";
        }
        else if(Piece[i] == 'Z'){
            Animal = "zebra:";
        }

        if(white){
            cout << "white " + Animal << pieces[Piece[i]] << endl;
        }
        else{
            cout << "white " + Animal << endl;
        }
        if(black){
            cout << "black " + Animal << pieces[Piece[i+1]] << endl;
        }
        else{
            cout << "black " + Animal << endl;
        }
        Animal = "";
        
    }
    

    if(pieces['x'] == "w"){
        cout << "side to play: white" << endl;
    }
    else{
        cout << "side to play: black" << endl;
    }



}


string SortMoves(string final){

    vector<string> vec ;
    string x = "";

    for(int i =0 ; i < final.length() ; i++){
        if(final[i] != ' '){
            x += final[i];
        }
        
        else{
            vec.push_back(x);
            x = "";
        }
    }

    vec.push_back(x);
    x ="";
    sort(vec.begin() , vec.end());

    for(int i = 0 ; i < vec.size() ; i++){
        if(i ==0){
            x += vec[i];
        }
        else{
            x += " " + vec[i];
        }
    }

    return x;
}


string GenLionMoves(map<char,string> Locations , vector<vector<char> > Board){

    
    string x;
    string move;
    string final = "";
    char c = 'a';
    int col;
    int row;

    if(Locations['x'] == "w"){

        x = Locations['L'];
        col = x[0] - 'a';
        row = x[1] - '0' - 1 ;
       //cross river left

        if(row == 2 && col == 4){

            if(Board[row + 1][col - 1] == '0'){

                if(Board[row + 2][col -2] == 'l'){

                    c += (col - 2);
                    move = x + c + to_string(row +3);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }   

            }
            
        }
       
        //ADD LEFT
        if(col - 1 >= 2){

            //DIAG LEFT BACK
            if(row -1 >= 0){
                
                if(Board[row - 1][col-1] == tolower(Board[row - 1][col-1])){
                
                    c += (col -1);
                    move = x + (c + to_string(row));
                    
                    if(final.length() == 0){
                            final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }

            //LEFT 
            if(Board[row][col-1] == tolower(Board[row][col-1])){
                c += (col-1);
            
                move = x + c + to_string(row + 1);
                if(final.length() == 0){
                        final += move;
                }
                else{
                    final += " " + move;
                }
                c = 'a';
            }

            //DIAG TOP LEFT
            if(row + 1 < 3){

                if(Board[row + 1][col - 1] == tolower(Board[row + 1][col - 1])){

                    c += (col -1);

                    move = x + c + to_string(row +2);
                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }

            }


        }
        
        //BACK
        if(row -1 >= 0){
            if(Board[row - 1][col] == tolower(Board[row - 1][col])){

                move = x + (x[0] + to_string(row));
                
                if(final.length() == 0){
                        final += move;
                }
                else{
                    final += " " + move;
                }

            }
        }

        //ONE STEP FORWARD
        if(row + 1 < 3 ){

            if(Board[row + 1][col] == tolower(Board[row + 1][col])){

                move = x + (x[0] + to_string(row + 2));
                
                if(final.length() == 0){
                        final += move;
                }
                else{
                    final += " " + move;
                }

            }
        }

        //check forward to other lion
        for(int i = row+1 ; i < 7 ; i++){

            if(Board[i][col] != '0'){

                if(Board[i][col] == 'l'){
                   
                    move = x + (x[0] + to_string(i + 1));
                    
                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    break;
                }
                else{
                    break;
                }
            }

        }

    

        //RIGHT
        if(col + 1 <= 4){

            //DIAG BACK RIGHT
            if(row - 1 >= 0){

                //diag back right
                if(Board[row - 1][col + 1] == tolower(Board[row - 1][col + 1])){
                
                    c += (col + 1);
                    move = x + (c + to_string(row));
                    
                    if(final.length() == 0){
                            final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
        
            }
            
            

            //RIGHT
            if(Board[row][col+1] == tolower(Board[row][col+1])){
                c += (col+1);
                move = x + c + to_string(row + 1);

                if(final.length() == 0){

                    final += move;
                }
                else{

                    final += " " + move;
                }
                c ='a';
            }

             //cross river right
            if(row == 2 && col == 2){

                if(Board[row + 1][col + 1] == '0'){

                    if(Board[row + 2][col + 2] == 'l'){

                        c += (col + 2);
                        move = x + c + to_string(row +3);

                        if(final.length() == 0){
                            final += move;
                        }
                        else{
                            final += " " + move;
                        }
                        c = 'a';
                    }

                }

            }


            //DIAG TOP RIGHT
            if(row + 1 < 3){

                if(Board[row + 1][col + 1] == tolower(Board[row + 1][col + 1])){

                    c += (col +1);

                    move = x + c + to_string(row +2);
                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }

            }
            
        } 

    }

    else{
        x = Locations['l'];
        col = x[0] - 'a';
        row = x[1] - '0' - 1 ;
        
        //River cross left
         if(row == 4 && col == 4){

            if(Board[row - 1][col - 1] == '0'){

                if(Board[row - 2][col - 2] == 'L'){

                    c += (col - 2);
                    move = x + c + to_string(row + 1 - 2);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }

            }

        }
         
        //LEFT
        if(col - 1 >= 2){

            //diagonal left
            if(row - 1 > 3){

               

                
                if(Board[row - 1][col - 1] == toupper(Board[row - 1][col - 1])){

                    c += (col -1);

                    move = x + c + to_string(row);
                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }

            }
            
            //LEFT
            if(Board[row][col-1] == toupper(Board[row][col-1])){
                c += (col-1);
                
                move = x + c + to_string(row + 1);
                if(final.length() == 0){
                        final += move;
                }
                else{
                    final += " " + move;
                }
                c = 'a';
            }


            //diag back left
            if(row +1 <= 6){
                
                if(Board[row + 1][col-1] == toupper(Board[row + 1][col-1])){
                    
                    c += (col -1);
                    move = x + (c + to_string(row + 2));
                    
                    if(final.length() == 0){
                            final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }   
            }
            
        }

        //BACK
        if(row + 1 <= 6){
            
            if(Board[row + 1][col] == toupper(Board[row + 1][col])){

                move = x + (x[0] + to_string(row + 2));
                
                if(final.length() == 0){
                        final += move;
                }
                else{
                    final += " " + move;
                }

            }


        }

        //front to opp lion
        for(int i = row-1 ; i >= 0 ; i--){

            if(Board[i][col] != '0'){

                if(Board[i][col] == 'L'){
                   
                    move = x + (x[0] + to_string(i + 1));
                    
                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    break;
                }
                else{
                    break;
                }
            }
        }

        //move forward one step
        if(row - 1 > 3 ){

            if(Board[row - 1][col] == toupper(Board[row - 1][col])){

                move = x + (x[0] + to_string(row));
                
                if(final.length() == 0){
                        final += move;
                }
                else{
                    final += " " + move;
                }

            }
        }
    
        //RIGHT
        if(col + 1 <= 4){

            //DIAG TOP RIGHT
            if(row - 1 > 3){

                if(Board[row - 1][col + 1] == toupper(Board[row - 1][col + 1])){

                    c += (col +1);

                    move = x + c + to_string(row);
                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }

            }
            //River cross right
            if(row == 4 && col == 2){

                if(Board[row - 1][col + 1] == '0'){

                    if(Board[row - 2][col + 2] == 'L'){

                        c += (col + 2);
                        move = x + c + to_string(row + 1 - 2);

                        if(final.length() == 0){
                            final += move;
                        }
                        else{
                            final += " " + move;
                        }
                        c = 'a';
                    }

                }

            }

            //RIGHT
            if(Board[row][col+1] == toupper(Board[row][col+1])){
            
                c += (col+1);
                move = x + c + to_string(row + 1);

                if(final.length() == 0){

                    final += move;
                }
                else{

                    final += " " + move;
                }
                c ='a';
            }

            //DIAG BACK RIGHT
            if(row +1 <= 6){
                      
                if(Board[row + 1][col + 1] == toupper(Board[row + 1][col + 1])){
                
                    c += (col + 1);
                    move = x + (c + to_string(row+2));
                    
                    if(final.length() == 0){
                            final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
                
            }
            
        }
    }
    
    if(final != ""){
        
        string x = SortMoves(final);
        return x;
    
    }
    else{
        return "";
    }
    
  
}


string GenZebraMoves(map<char,string> Locations , vector<vector<char> > Board){

    string x;
    string move;
    string final = "";
    char c = 'a';
    int col;
    int row;
    bool Exists = true;

    if(Locations['x'] == "w"){

        //check if there is a White zebra
        Exists = Locations.find('Z') != Locations.end();
        if(!Exists){
            return final;
        }

        x = Locations['Z'];
        col = x[0] - 'a';
        row = x[1] - '0' - 1 ;

        //TWO LEFT (FAR)
        if(col - 2 >= 0){

            //ONE UP
            if(row -1 >= 0){
                
                if(Board[row -1][col - 2] == tolower(Board[row -1][col - 2])){
                    c += col-2;
                    move = x + c + to_string(row);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }

            //ONE DOWN
            if(row + 1 <= 6){

                //we can take 
                if(Board[row+1][col-2] == tolower(Board[row+1][col-2])){
                    c += col-2;
                    move = x + c + to_string(row + 2);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //TOP LEFT 
        if(row - 2 >= 0){
            //The LEFT
            if(col -1 >= 0){

                if(Board[row - 2][col -1] == tolower(Board[row - 2][col -1])){
                    c += col-1;
                    move = x + c + to_string(row - 1);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //Bottom Left
        if(row + 2 <= 6){
            //The LEFt
            if(col -1 >= 0){
                if(Board[row +2][col -1] == tolower(Board[row +2][col -1])){
                    c += col-1;
                    move = x + c + to_string(row + 3);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //TOP Right
        if(row - 2 >= 0){
            //The Right
            if(col + 1 <= 6){

                if(Board[row - 2][col + 1] == tolower(Board[row - 2][col + 1])){
                    c += col+1;
                    move = x + c + to_string(row - 1);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //Bottom Right
        if(row + 2 <= 6){
            //The Right
            if(col + 1 <= 6){
                if(Board[row +2][col + 1] == tolower(Board[row +2][col + 1])){
                    c += col + 1;
                    move = x + c + to_string(row + 3);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //The far Right
        if(col + 2 <=6){
            //The Top
            if(row - 1 >= 0){

                if(Board[row - 1][col + 2] == tolower(Board[row - 1][col + 2])){
                    c += col + 2;
                    move = x + c + to_string(row);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }

            //The Bottom
            if(row + 1 <= 6){

                if(Board[row + 1][col + 2] == tolower(Board[row + 1][col + 2])){
                    c += col + 2;
                    move = x + c + to_string(row + 2 );

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

    }

    else{

        //check if there is a Black zebra
        Exists = Locations.find('z') != Locations.end();
        if(!Exists){
            return final;
        }

        x = Locations['z'];
        col = x[0] - 'a';
        row = x[1] - '0' - 1 ;

        //TWO LEFT (FAR)
        if(col - 2 >= 0){

            //ONE UP
            if(row - 1 >= 0){
                
                if(Board[row -1][col - 2] == toupper(Board[row -1][col - 2])){
                    c += col-2;
                    move = x + c + to_string(row);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }

            //ONE DOWN
            if(row + 1 <= 6){

                //we can take 
                if(Board[row+1][col-2] == toupper(Board[row+1][col-2])){
                    c += col-2;
                    move = x + c + to_string(row + 2);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //TOP LEFT 
        if(row - 2 >= 0){
            //The LEFT
            if(col -1 >= 0){

                if(Board[row - 2][col -1] == toupper(Board[row - 2][col -1])){
                    c += col-1;
                    move = x + c + to_string(row - 1);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //Bottom Left
        if(row + 2 <= 6){
            //The LEFt
            if(col -1 >= 0){
                if(Board[row +2][col -1] == toupper(Board[row +2][col -1])){
                    c += col-1;
                    move = x + c + to_string(row + 3);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }
    
        //TOP Right
        if(row - 2 >= 0){
            //The Right
            if(col + 1 <= 6){

                if(Board[row - 2][col + 1] == toupper(Board[row - 2][col + 1])){
                    c += col+1;
                    move = x + c + to_string(row - 1);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //Bottom Right
        if(row + 2 <= 6){
            //The Right
            if(col + 1 <= 6){
                if(Board[row +2][col + 1] == toupper(Board[row +2][col + 1])){
                    c += col + 1;
                    move = x + c + to_string(row + 3);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

        //The far Right
        if(col + 2 <=6){
            //The Top
            if(row - 1 >= 0){

                if(Board[row - 1][col + 2] == toupper(Board[row - 1][col + 2])){
                    c += col + 2;
                    move = x + c + to_string(row);

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }

            //The Bottom
            if(row + 1 <= 6){

                if(Board[row + 1][col + 2] == toupper(Board[row + 1][col + 2])){
                    c += col + 2;
                    move = x + c + to_string(row + 2 );

                    if(final.length() == 0){
                        final += move;
                    }
                    else{
                        final += " " + move;
                    }
                    c = 'a';
                }
            }
        }

    }   

    return final;
    
}


string GenElephantMoves(map<char,string> Locations , vector<vector<char> > Board){

    string x;
    string move;
    string final = "";
    char c = 'a';
    int col;
    int row;
    bool Exists = true;

    if(Locations['x'] == "w"){

        //check if there is a White Elephant
        Exists = Locations.find('E') != Locations.end();
        if(!Exists){
            return final;
        }
        //add the space to the end for that extra position
        x = Locations['E'] + ' ';
        
        string pos = "";
        
        for(int i = 0 ; i < x.length() ; i++){

            if(x[i] != ' '){
                pos += x[i];
            }
            //move calc
            else{

                col = pos[0] - 'a';
                row = pos[1] - '0' - 1 ;

                //Add Far Left
                if(col - 2 >= 0){

                    if(Board[row][col -2] == tolower(Board[row][col -2])){
                        c += col-2;
                        move = pos + c + to_string(row + 1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                //The left
                if(col -1 >= 0){

                    if(Board[row][col -1] == tolower(Board[row][col -1])){
                        c += col-1;
                        move = pos + c + to_string(row + 1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                //The Top (FAR)
                if(row - 2 >= 0){

                    if(Board[row -2][col] == tolower(Board[row -2][col])){
                        c += col;
                        move = pos + c + to_string(row - 1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
                
                //The Top
                if(row - 1 >= 0){

                    if(Board[row - 1][col] == tolower(Board[row - 1][col])){
                        c += col;
                        move = pos + c + to_string(row);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                //The Bottom
                if(row + 1 <= 6){

                    if(Board[row + 1][col] == tolower(Board[row + 1][col])){
                        c += col;
                        move = pos + c + to_string(row + 2);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
                
                //The Far Bottom
                if(row + 2 <= 6){

                    if(Board[row + 2][col] == tolower(Board[row + 2][col])){
                        c += col;
                        move = pos + c + to_string(row + 3);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                //The Right
                if(col + 1 <= 6){

                    if(Board[row][col +1] == tolower(Board[row][col +1])){
                        c += col + 1;
                        move = pos + c + to_string(row +1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
                
                //The Far Right
                if(col + 2 <= 6){

                    if(Board[row][col + 2] == tolower(Board[row][col + 2])){
                        c += col + 2;
                        move = pos + c + to_string(row +1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
                //Reset the string
                pos = "";
            }
        }

    }

    else{

        //check if there is a Black Elephant
        Exists = Locations.find('e') != Locations.end();
        if(!Exists){
            return final;
        }
        
        //add the space to the end for that extra position
        x = Locations['e'] + ' ';
        
        string pos = "";

        for(int i = 0 ; i < x.length() ; i++){
            
            if(x[i] != ' '){
                pos += x[i];
            }
            else{

                col = pos[0] - 'a';
                row = pos[1] - '0' - 1 ;

                //Add Far Left
                if(col - 2 >= 0){

                    if(Board[row][col -2] == toupper(Board[row][col -2])){
                        c += col-2;
                        move = pos + c + to_string(row + 1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
                
                //The left
                if(col - 1 >= 0){

                    if(Board[row][col -1] == toupper(Board[row][col -1])){
                        c += col-1;
                        move = pos + c + to_string(row + 1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                //The Top (FAR)
                if(row - 2 >= 0){

                    if(Board[row -2][col] == toupper(Board[row -2][col])){
                        c += col;
                        move = pos + c + to_string(row - 1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
            
                //The Top
                if(row - 1 >= 0){

                    if(Board[row - 1][col] == toupper(Board[row - 1][col])){
                        c += col;
                        move = pos + c + to_string(row);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
            
                //The Bottom
                if(row + 1 <= 6){

                    if(Board[row + 1][col] == toupper(Board[row + 1][col])){
                        c += col;
                        move = pos + c + to_string(row + 2);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }
            
                //The Far Bottom
                if(row + 2 <= 6){

                    if(Board[row + 2][col] == toupper(Board[row + 2][col])){
                        c += col;
                        move = pos + c + to_string(row + 3);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                //The Right
                if(col + 1 <= 6){

                    if(Board[row][col +1] == toupper(Board[row][col +1])){
                        c += col + 1;
                        move = pos + c + to_string(row +1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                //The Far Right
                if(col + 2 <= 6){

                    if(Board[row][col + 2] == toupper(Board[row][col + 2])){
                        c += col + 2;
                        move = pos + c + to_string(row +1);

                        if(final.length() == 0){
                           final += move;
                        }
                        else{
                          final += " " + move;
                        }
                        c = 'a';
                    }
                }

                pos = "";
            }
        }



    }

    return final;


}


string GenPawnMoves(map<char,string> Locations , vector<vector<char> > Board){

    string x;
    string move;
    string final = "";
    char c = 'a';
    int col;
    int row;
    bool Exists = true;

    if(Locations['x'] == "w"){

        //check if there is White Pawns
        Exists = Locations.find('P') != Locations.end();
        if(!Exists){
            return final;
        }
        //add the space to the end for that extra position
        x = Locations['P'] + ' ';
        string pos = "";

        for(int i =0 ; i < x.length() ; i++){

            if(x[i] != ' '){
                pos += x[i];
            }
            else{

                col = pos[0] - 'a';
                row = pos[1] - '0' - 1 ;

                //if Past River
                if(row >= 4){
                    //Add top left
                    if(row + 1 <= 6){

                        //Left
                        if(col - 1 >= 0){

                            if(Board[row + 1][col - 1] == tolower(Board[row + 1][col - 1])){
                                c += col - 1;
                                move = pos + c + to_string(row + 2);

                                if(final.length() == 0){
                                    final += move;
                                }
                                else{
                                    final += " " + move;
                                }
                                c = 'a';
                            }
                        }                          
                    }     

                    //Add Double Bottom
                    if(Board[row - 2][col] == '0'){
                        //if the back  is free then we can double bottom
                        if(Board[row -1][col] == '0'){
                            c += col;
                            move = pos + c + to_string(row - 1);

                            if(final.length() == 0){
                                final += move;
                            }
                            else{
                                final += " " + move;
                            }
                            c = 'a'; 
                        }  
                    }

                    //Add Bottom
                    if(Board[row -1][col] == '0'){
                        c += col;
                        move = pos + c + to_string(row);

                        if(final.length() == 0){
                            final += move;
                        }
                        else{
                            final += " " + move;
                        }
                        c = 'a'; 
                    }
                    
                    //Top
                    if(row + 1 <= 6){

                        if(Board[row + 1][col] == tolower(Board[row + 1][col])){

                        c += col;
                        move = pos + c + to_string(row + 2);

                        if(final.length() == 0){
                            final += move;
                        }
                        else{
                            final += " " + move;
                        }
                        c = 'a';  
                    }

                    }
                    
                    //top right
                    if(row + 1 <= 6){

                        if(col + 1 <= 6){

                            if(Board[row + 1][col + 1] == tolower(Board[row + 1][col + 1])){
                                c += col + 1;
                                move = pos + c + to_string(row + 2);

                                if(final.length() == 0){
                                    final += move;
                                }
                                else{
                                    final += " " + move;
                                }
                                c = 'a';
                            }
                        }  
                    }
                    
                }
                //its on its side can capture
                else{

                    //Add top left
                    if(col -1 >= 0){

                        if(Board[row + 1][col -1] == tolower(Board[row + 1][col -1])){
                            c += col - 1;
                            move = pos + c + to_string(row + 2);

                            if(final.length() == 0){
                                final += move;
                            }
                            else{
                                final += " " + move;
                            }
                            c = 'a';
                        }
                    }
                    
                    //Add Top
                    if(Board[row +1][col] == tolower(Board[row +1][col])){
                        c += col;
                        move = pos + c + to_string(row + 2);

                        if(final.length() == 0){
                            final += move;
                        }
                        else{
                            final += " " + move;
                        }
                        c = 'a';
                    }
                    
                    //top Right
                    if(col + 1 <= 6){

                        if(Board[row +1][col +1] == tolower(Board[row +1][col +1])){
                            c += col + 1;
                            move = pos + c + to_string(row + 2);

                            if(final.length() == 0){
                                 final += move;
                            }
                            else{
                                final += " " + move;
                            }
                            c = 'a';
                         }
                    }
                    
                }

                pos = "";
            }
        }

    }

    else{

        //check if there is  Black Pawns
        Exists = Locations.find('p') != Locations.end();
        if(!Exists){
            return final;
        }
        //add the space to the end for that extra position
        x = Locations['p'] + ' ';
        string pos = "";

        for(int i = 0 ; i < x.length() ; i++){

            if(x[i] != ' '){
                pos += x[i];
            }
            else{
                col = pos[0] - 'a';
                row = pos[1] - '0' - 1 ;
                
                //across the river
                if(row <= 2){

                    //Add top left
                    if(row - 1 >= 0){
                        //Left
                        if(col - 1 >= 0){

                            if(Board[row - 1][col - 1] == toupper(Board[row - 1][col - 1])){
                                c += col - 1;
                                move = pos + c + to_string(row);

                                if(final.length() == 0){
                                final += move;
                                }
                                else{
                                final += " " + move;
                                }
                                c = 'a';
                            }
                        }                          
                    } 

                    //Add Forward
                    if(row - 1 >= 0){

                        if(Board[row - 1][col] == toupper(Board[row - 1][col])){
                            c += col;
                            move = pos + c + to_string(row);

                            if(final.length() == 0){
                            final += move;
                            }
                            else{
                            final += " " + move;
                            }
                            c = 'a';
                        }
                    }

                    //Add back
                    if(Board[row + 1][col] == '0'){
                        c += col;
                        move = pos + c + to_string(row+2);

                        if(final.length() == 0){
                        final += move;
                        }
                        else{
                        final += " " + move;
                        }
                        c = 'a';
                    }

                    //Add Double Back
                    if(Board[row + 2][col] == '0'){
                        //add double back if back is free
                        if(Board[row + 1][col] == '0'){
                            c += col;
                            move = pos + c + to_string(row + 3);

                            if(final.length() == 0){
                            final += move;
                            }
                            else{
                            final += " " + move;
                            }
                            c = 'a';
                        }
                    }

                    //Add Top Right
                    if(row - 1 >= 0){

                        if(col + 1 <= 6){

                            if(Board[row - 1][col + 1] == toupper(Board[row - 1][col + 1])){
                                
                                c += col + 1;
                                move = pos + c + to_string(row);

                                if(final.length() == 0){
                                final += move;
                                }
                                else{
                                final += " " + move;
                                }
                                c = 'a';
                        
                            }
                        }
                    }
                        
                
                }
                //its on its side it can capture
                else{

                    //Add Top Left
                    if(col - 1 >= 0){

                        if(Board[row - 1][col -1] == toupper(Board[row - 1][col -1])){

                            c += col - 1;
                            move = pos + c + to_string(row);

                            if(final.length() == 0){
                            final += move;
                            }
                            else{
                            final += " " + move;
                            }
                            c = 'a';
                        }   
                    }

                    //Add Top
                    if(Board[row - 1][col] == toupper(Board[row - 1][col])){
                        c += col;
                        move = pos + c + to_string(row);

                        if(final.length() == 0){
                        final += move;
                        }
                        else{
                        final += " " + move;
                        }
                        c = 'a';
                    }

                    //add Top right
                    if(col + 1 <= 6){

                        if(Board[row - 1][col + 1] == toupper(Board[row - 1][col + 1])){

                            c += col + 1;
                            move = pos + c + to_string(row);

                            if(final.length() == 0){
                            final += move;
                            }
                            else{
                            final += " " + move;
                            }
                            c = 'a';
                        } 
                    }
                }

                pos = "";
            }
        }

    }

    return final;
}


string DoMove(map<char,string> Locations  , string move , vector<vector<char> > &Board){

    //get start and end board positions
    int Srow;
    int SCol;
    int Erow;
    int ECol;

    SCol = move[0] - 'a';
    Srow  = move[1] - '0' - 1 ;
    
    ECol = move[2] - 'a';
    Erow = move[3] - '0' - 1;


    //get piece in river if any?
    int Rcol = -1;
    int Rrow = 3;
    for(int i = 0 ; i < 7 ; i++){

        if((i == SCol) && (Srow == 3)){
            continue;
        }
        
        if(Locations['x'] == "w"){
            if(Board[3][i] != '0' && Board[3][i] != tolower(Board[3][i])){
                Rcol = i;
                break;
            }
        }
        else{
            if(Board[3][i] != '0' && Board[3][i] != toupper(Board[3][i])){
                Rcol = i;
                break;
            }
        }
        
    }
    

    //Do move
    char State = Board[Srow][SCol];

    Board[Srow][SCol] = '0';
    Board[Erow][ECol] = State;
    //if we start and end in the river we drown
    if((Srow == 3) && (Erow == 3)){
        Board[Erow][ECol] = '0';
    }

    //Drown piece
    //we have a piece to drown
    if(Rcol != -1){
        
        Board[Rrow][Rcol] = '0';
        
    }

    string Fen = "";
    int count = 0;
    for(int i =6 ; i >= 0 ; i--){

        for(int j = 0 ; j < 7 ; j++){
            

            if(Board[i][j] == '0'){
                count++;
            }
            else if(Board[i][j] != '0'){

                if(count == 0){
                    Fen += Board[i][j];
                }
                else{

                    Fen += to_string(count) + Board[i][j];
                }
                
                count = 0;
            }

            if(count != 0 &&  j==6){
                Fen += to_string(count);
                count = 0;
            }

        }
        if(i != 0){
            Fen += '/';
        }
        

    }

    if(Locations['x'] == "w"){
        Fen += " b ";
        //same counter
        Fen += Locations['y'];
    }
    else{
        
        Fen += " w ";
        //increment counter
        string co = Locations['y'];
        int newcount = stoi(co);
        newcount++;
        Fen += to_string(newcount);
    }
    

    return Fen;
        
}


int CalcWhite(map<char,string> Locations){
    bool pawns = Locations.find('P') != Locations.end();
    bool elephants = Locations.find('E') != Locations.end();
    bool zebras = Locations.find('Z') != Locations.end();
    string x = "";
    int Total = 0;
    //Pawns
    if(pawns == true){

        x = Locations['P'] + ' ';

        for(int i = 0 ; i < x.length() ;i++){
            if(x[i] == ' '){
                Total += 100;
            }
        }
    }
    if(elephants == true){

        x = Locations['E'] + ' ';

        for(int i = 0 ; i < x.length() ;i++){
            if(x[i] == ' '){
                Total += 200;
            }
        }
    }
    if(zebras == true){

        x = Locations['Z'] + ' ';

        for(int i = 0 ; i < x.length() ;i++){
            if(x[i] == ' '){
                Total += 300;
            }
        }
    }

    return Total;
    
}


int CalcBlack(map<char,string> Locations){
    bool pawns = Locations.find('p') != Locations.end();
    bool elephants = Locations.find('e') != Locations.end();
    bool zebras = Locations.find('z') != Locations.end();
    string x = "";
    int Total = 0;
    //Pawns
    if(pawns == true){

        x = Locations['p'] + ' ';

        for(int i = 0 ; i < x.length() ;i++){
            if(x[i] == ' '){
                Total += 100;
            }
        }
    }
    if(elephants == true){

        x = Locations['e'] + ' ';

        for(int i = 0 ; i < x.length() ;i++){
            if(x[i] == ' '){
                Total += 200;
            }
        }
    }
    if(zebras == true){

        x = Locations['z'] + ' ';

        for(int i = 0 ; i < x.length() ;i++){
            if(x[i] == ' '){
                Total += 300;
            }
        }
    }

    return Total;
    
}


int Evaulation(map<char,string> Locations){
    //check for lions
    bool Wlion = Locations.find('L') != Locations.end();
    bool Blion = Locations.find('l') != Locations.end();
    //if there are only two pieces its a draw

    if(Locations.size() == 4 && Wlion == true && Blion == true){
      
        return 0;
    }
    //check for missing lions
    else if(Wlion == false){
    
        if(Locations['x'] == "b"){
            return -1 * -10000;
        }
        return -10000;    
    }
    else if(Blion == false){            
   
        if(Locations['x'] == "b"){
            return -1 * 10000;
        }
        return 10000;
    } 
    else{
        //calc total white
        int WhiteValue = CalcWhite(Locations);
        //cala total black
        int BlackValue = CalcBlack(Locations);
        
        int RawScore = WhiteValue - BlackValue;
        // if black is playing multiply by -1
        // if(Locations['x'] == "b"){
        //     RawScore = (-1) * (RawScore);
        // }
        return RawScore;
    }
   
}


bool isGameOver(map<char,string> Locations){

    bool Wlion = Locations.find('L') != Locations.end();
    bool Blion = Locations.find('l') != Locations.end();

    if(Wlion == false || Blion == false){
        return true;
    }
    else{
        return false;
    }
}


void GenMoves(map<char,string> Locations,vector<string> &moves , vector<vector<char> > Board){

    string temp = "";
    string x;
    x = GenZebraMoves(Locations , Board);
    if(x != ""){
        x += ' ';
        
        for(int i = 0 ; i < x.length() ;i++){

            if(x[i] != ' '){
                temp += x[i];
            }
            else{

                moves.push_back(temp);
                temp = "";
            }
        }
    }

    x = GenElephantMoves(Locations , Board);
    if(x != ""){
        x += ' ';
        
        for(int i = 0 ; i < x.length() ;i++){

            if(x[i] != ' '){
                temp += x[i];
            }
            else{

                moves.push_back(temp);
                temp = "";
            }
        }
    }


    

    x = GenLionMoves(Locations , Board);
    
    if(x != ""){
        x += ' ';
        
        for(int i = 0 ; i < x.length() ;i++){

            if(x[i] != ' '){
                temp += x[i];
            }
            else{

                moves.push_back(temp);
                temp = "";
            }
        }
    }

    x = GenPawnMoves(Locations , Board);

    if(x != ""){
        x += ' ';
        
        for(int i = 0 ; i < x.length() ;i++){

            if(x[i] != ' '){
                temp += x[i];
            }
            else{

                moves.push_back(temp);
                temp = "";
            }
        }
    }


}


int WhiteAttack(map<char,string> Locations,vector<string> WhiteMoves){

    vector<vector<char> > Board = GenBoard(Locations);

    int Total = 0;

    for(int i = 0 ; i < WhiteMoves.size() ; i++){
        string move = WhiteMoves[i];
        int ECol = move[2] - 'a';
        int Erow = move[3] - '0' - 1;

        if(Board[Erow][ECol] != '0'){

            if(Board[Erow][ECol] == tolower(Board[Erow][ECol])){
                Total += 1;
                if(Board[Erow][ECol] == 'l'){
                    Total += 10;
                }
            }
            
        }
           

    }

    return Total;

}


int BlackAttack(map<char,string> Locations,vector<string> BlackMoves){

    vector<vector<char> > Board = GenBoard(Locations);

    int Total = 0;

    for(int i = 0 ; i < BlackMoves.size() ; i++){
        string move = BlackMoves[i];
        int ECol = move[2] - 'a';
        int Erow = move[3] - '0' - 1;

        if(Board[Erow][ECol] != '0'){

            if(Board[Erow][ECol] == toupper(Board[Erow][ECol])){
                Total += 1;

                if(Board[Erow][ECol] == 'L'){
                    Total += 10;
                }
            }
            
        }
        
    }

    return Total;

}


int AdvancedEvaluation(map<char,string> Locations , vector<vector<char> > Board){

    

    //check for lions
    bool Wlion = Locations.find('L') != Locations.end();
    bool Blion = Locations.find('l') != Locations.end();
    //if there are only two pieces its a draw

    if(Locations.size() == 4 && Wlion == true && Blion == true){
        return 0;
    }
    //check for missing lions
    else if(Wlion == false){
    
        if(Locations['x'] == "b"){
            return -1 * -10000;
        }
        return -10000;    
    }
    else if(Blion == false){            
   
        if(Locations['x'] == "b"){
            return -1 * 10000;
        }
        return 10000;
    }
    else{

        int Material = Evaulation(Locations);
        file << "Material Score is : " << Material << endl;
        //gen white moves
        vector<string> WhiteMoves;
        vector<string> BlackMoves;

        if(Locations['x'] == "w"){

            GenMoves(Locations, WhiteMoves , Board);

            //gen black moves
            map<char,string> BlackPositions = Locations;
            BlackPositions['x'] = "b";
            GenMoves(BlackPositions, BlackMoves , Board);
        }
        else{
            GenMoves(Locations, BlackMoves , Board);

            //gen white moves
            map<char,string> WhitePositions = Locations;
            WhitePositions['x'] = "w";
            GenMoves(WhitePositions, WhiteMoves  , Board);
        }

        //calc mobility
        int Mobility = WhiteMoves.size() - BlackMoves.size();
        file << "Num of White moves : " << WhiteMoves.size() << endl;
        file << "Num of Black moves : " << BlackMoves.size() << endl;
        file << "Mobility is : " << Mobility << endl;


        //cal attack
        int WAttack = WhiteAttack(Locations ,WhiteMoves);
        int BAttack = BlackAttack(Locations , BlackMoves);

        int Attack = WAttack - BAttack;

        file << "White Attack Score : " << WAttack << endl;
        file << "Black Attack Score : " << BAttack << endl;
        file << "Attack is : " << Attack << endl;

        int Sum = Material + Mobility + Attack;

        if(Locations['x'] == "b"){
            return -1 * Sum;
        }
        return Sum;
    }

}


int MiniMax(map<char,string> CurrentState , int depth , string &BestMove , bool first){

    if(isGameOver(CurrentState) == true || depth <= 0){

        return Evaulation(CurrentState);
        
    }
    int value = -10000000;
    vector<vector<char> > Board = GenBoard(CurrentState);

    vector<string> moves;
    GenMoves(CurrentState , moves , Board);
    
    for(string move : moves){
    
        string NextState = DoMove(CurrentState , move , Board);
        map<char,string> newState = GetPositions(NextState);
        int eval = -(MiniMax(newState , depth-1 , BestMove , false));

        if(eval > value){
            value = eval;
            if(first == true){
                BestMove = move;
            }
        }
    }

    return value;

}   


int AlphaBeta(map<char,string> &CurrentState , int depth , int alpha , int beta , string &BestMove , bool first){
    vector<vector<char> > Board = GenBoard(CurrentState);


    if(isGameOver(CurrentState) == true || depth <= 0){

        return AdvancedEvaluation(CurrentState , Board);
        
    }
    

    vector<string> moves;
    GenMoves(CurrentState , moves , Board);

    for(int i = 0 ; i < moves.size() ; i++){

        string move = moves[i];
        string NextState = DoMove(CurrentState , move , Board);
        map<char,string> newState = GetPositions(NextState);
        int eval = -AlphaBeta(newState , depth-1 ,-beta,-alpha , BestMove , false);

        if(eval >= beta){
            return beta;
        }
        if(eval > alpha){
            alpha = eval;
            if(first == true){
                BestMove = move;
            }
        }
        
    }

    return alpha;
}


string PlayGame(vector<vector<char> > &Board , map<char,string> Positions){

    string SideToPlay = "b";
    int moveCount = 0;

    while(moveCount < 100){

        string move = "";
        if(SideToPlay == "b"){

            int value = MiniMax(Positions , 3 , move , true);
        }
        else{

            int value = AlphaBeta(Positions , 5 ,-100000000,100000000 ,move , true);
            moveCount++;
        }   

        string NewFen = DoMove(Positions , move , Board);
        Positions = GetPositions(NewFen);  

        if(isGameOver(Positions)){
            return SideToPlay;
        }

        if(SideToPlay == "b"){
            SideToPlay = "w";
        }
        else{
            SideToPlay = "b";
        }
    }
    return "DRAW";
}




int main(){
    // file.open("output.txt" , ios::app);
    vector<string>Fens;
    
    int N;
    cin >> N;
    cin.ignore();

    for(int i = 0 ; i < N ; i ++){
        string fen;
        getline(cin,fen);
        Fens.push_back(fen);

    }

    for(int i = 0 ; i < Fens.size() ; i ++){
        
        map<char,string> loc = GetPositions(Fens[i]); 
        vector<vector<char> > Board = GenBoard(loc);
        vector<string> moves;
        GenMoves(loc , moves , Board);
        for(int i = 0 ; i < moves.size() ; ++i){
            cout << moves[i] << " ";
        }
        // file << AdvancedEvaluation(loc , Board) << endl;
        
    }
    
    return 0;
      
        
   
}
