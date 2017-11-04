#include <iostream>
#include<SFML/Graphics.hpp>
#include <time.h>
using namespace std;
using namespace sf;

#define BOARD_LENGTH 8
#define TOTAL_PIECE_COUNT 32
#define TEAM_SIZE 16
int size=56;//edge size of one square on the board, this is the foundation for all the location/position arithmetic
            //it's also how we will pull single piece images from figures.png as needed

Sprite pieces[TOTAL_PIECE_COUNT]; //pieces

//negatives correspond to black, positives to white
int board[BOARD_LENGTH][BOARD_LENGTH]={
    -1,-2,-3,-4,-5,-3,-2,-1,
    -6,-6,-6,-6,-6,-6,-6,-6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 6, 6,
    1, 2, 3, 4, 5, 3, 2, 1
};
/*transformed via x=abs(n)-1 and y=(n>0)?1:0 we get this grid of pairs
 * The cordinates correspond to the rectangle from figures.png that contains the texture needed for that piece
    (0,0),(1,0),(2,0),(3,0),(4,0),(2,0),(1,0),(0,0),
    (5,0),(5,0),(5,0),(5,0),(5,0),(5,0),(5,0),(5,0),
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (5,1),(5,1),(5,1),(5,1),(5,1),(5,1),(5,1),(5,1),
    (0,1),(1,1),(2,1),(3,1),(4,1),(2,1),(1,1),(0,1)
*/

void loadPosition(){
    int k=0;
    int i,j,n,x,y;
    for(i=0;i<BOARD_LENGTH;i++)
        for(j=0;j<BOARD_LENGTH;j++){
            n=board[i][j];//get the 'key' value for that slot
            if (!n) continue;//jump to next iter
            x = abs(n)-1;
            y= (n>0) ? 1:0;//find if its black or white
            pieces[k].setTextureRect( IntRect(size*x,size*y,size,size));//IntRect(leftSide, TopSide, width, height)
            pieces[k].setPosition(size*j,size*i);//set it in the current box
            k++;
        }

}

int main() {
    RenderWindow window(VideoMode(453,453),"Chess!");

    Texture t1,t2;
    t1.loadFromFile("figures.png");
    t2.loadFromFile("board0.png");

    Sprite sprite(t1);
    Sprite sBoard(t2);

    //bind all pieces to our stock figures.png, they will obtain a cut of it using IntRect() in loadPosition()
    for(int i=0;i<TOTAL_PIECE_COUNT;i++) pieces[i].setTexture(t1);
    loadPosition();

    bool isMove=false;
    float dx=0, dy=0;

    while(window.isOpen()){
        Vector2i pos = Mouse::getPosition(window);
        Event e;
        while(window.pollEvent(e)){
            if(e.type==Event::Closed)
                window.close();

            //drag and drop
            if(e.type== Event::MouseButtonPressed)
                if(e.key.code==Mouse::Left)
                    if(sprite.getGlobalBounds().contains(pos.x,pos.y)){
                        isMove=true;
                        dx=pos.x-sprite.getPosition().x;
                        dy=pos.y-sprite.getPosition().y;
                    }

            if(e.type==Event::MouseButtonReleased)
                if(e.key.code==Mouse::Left)
                    isMove=false;
        }

        if(isMove) sprite.setPosition(pos.x-dx,pos.y-dy);

        window.clear();
        window.draw(sBoard);
        for(int i=0;i<TOTAL_PIECE_COUNT;i++)
            window.draw(pieces[i]);
        window.display();
    }
    return 0;
}