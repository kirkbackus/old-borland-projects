//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "poker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
//Declare global variables
String cards[13][4];

//Vars for Cunstom Window
bool drag;
int x,y;
POINT curpos;

//Create Player
Player player;
Player dealer;

//For Stages
int stage = 0;
String Steps;

//Card Control Array
TImage *ImgCards[10];
bool cardsUsed[5]={0};
bool clicked=0;

//Region for cool looking window
HRGN rgn;
HWND hwnd;
HDC hdc;

Deck deck;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  DoubleBuffered = 1;

  randomize(); //Randomize BEFORE you shuffle the deck
  deck.Shuffle(120); //Shuffle the deck (120 iterations)
  rgn = CreateRoundRectRgn(4,38,Form1->Width-4,Form1->Height-4,32,32);
  SetWindowRgn(Form1->Handle,rgn,1);
  Title->OnMouseDown = TitleBar->OnMouseDown;

  ImgCards[0]=PCard1;
  ImgCards[1]=PCard2;
  ImgCards[2]=PCard3;
  ImgCards[3]=PCard4;
  ImgCards[4]=PCard5;
  ImgCards[5]=CCard1;
  ImgCards[6]=CCard2;
  ImgCards[7]=CCard3;
  ImgCards[8]=CCard4;
  ImgCards[9]=CCard5;

  GameInfo->Caption = "First you will be delt 5 cards and then\nyou will choose any number of cards\nto discard. Then you and the dealer\nwill show your hands and the computer\ndetermines who wins";

  Cards->GetBitmap(0,Card1->Picture->Bitmap);
  for (int i=0;i<10;i++) Cards->GetBitmap(0,ImgCards[i]->Picture->Bitmap);

  //Deal Players Hand
  for (int i=0;i<5;i++) {
    player.SetCard(i,deck.NextCard());
    int ncard = player.GetCard(i);
    Cards->GetBitmap(ncard,ImgCards[i]->Picture->Bitmap);
    ImgCards[i]->Refresh();
  }

  //Label1->Caption = player.NameOfHand(player.GetHandType());

  //Deal Computers Hand
  for (int i=0;i<5;i++) {
    dealer.SetCard(i,deck.NextCard());
  }

  Steps = "Choose cards you want to \ndiscard\n\nThen click on the deck when\nyou are done";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GameTimerTimer(TObject *Sender)
{
  //Get the Cursor Position
  GetCursorPos(&curpos);
  curpos.x -= Form1->Left;
  curpos.y -= Form1->Top;

  //Update Label's
  LWins->Caption = "Player Wins: "+(String)player.GetWins()+"\nDealer Wins: "+(String)dealer.GetWins();
  LSteps->Caption = Steps;

  //For Dragging the Window
  if (drag) {
    if (GetAsyncKeyState(VK_LBUTTON)) {
      Form1->Left = curpos.x-x+Form1->Left;
      Form1->Top = curpos.y-y+Form1->Top;
    } else {
      drag = 0;
    }
  }

  //Control Quit Button
  if (curpos.x>=Quit->Left+4 && curpos.y>=Quit->Top+30 &&
  curpos.x<=Quit->Left+Quit->Width+4 && curpos.y<=Quit->Top+Quit->Height+30) {
    if (GetAsyncKeyState(VK_LBUTTON)){
      Quit->BevelOuter=bvLowered;
      Quit->Color = clMaroon;
    }
    else
      Quit->Color = (TColor)RGB(255,128,128);
  }
  else {
    Quit->Color = clRed;
    Quit->BevelOuter=bvRaised;
  }

  bool hover=0;
  for (int i=0;i<5;i++) {
    if (curpos.x> PlayerHand->Left+8+(i*74) && curpos.y>PlayerHand->Top+55
    && curpos.x<PlayerHand->Left+((i+1)*74)+6 && curpos.y<PlayerHand->Top+151 &&
    stage==0) {
      hover = 1;
      PSelect->Left = (8+(i*72));
      PSelect->Visible = 1;
      if (GetAsyncKeyState(VK_LBUTTON)) {
        if (cardsUsed[i]==0) {
          if (clicked==0) {
            int ncard=-1;
            cardsUsed[i]=1;
            //player.SetCard(i,ncard);
            Cards->GetBitmap(0,ImgCards[i]->Picture->Bitmap);
            ImgCards[i]->Refresh();
            clicked=1;
          }
        } else {
          if (clicked==0) {
            int ncard=-1;
            cardsUsed[i]=0;
            //player.SetCard(i,ncard);
            Cards->GetBitmap(player.GetCard(i),ImgCards[i]->Picture->Bitmap);
            ImgCards[i]->Refresh();
            clicked=1;
          }
        }
      } else clicked=0;
    }
  }
  
  if (!hover)PSelect->Visible = 0;

  if (GetAsyncKeyState(VK_LBUTTON)); //Just Used to Reset Button State
}
//---------------------------------------------------------------------------
void __fastcall TForm1::QuitClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TitleBarMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  drag = 1;
  x = curpos.x;
  y = curpos.y;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Card1Click(TObject *Sender)
{
  if (stage==0) {
    stage=1;
    for (int i=0;i<5;i++) {
      if (cardsUsed[i]) {
        player.SetCard(i,deck.NextCard());
        int ncard = player.GetCard(i);
        Cards->GetBitmap(ncard,ImgCards[i]->Picture->Bitmap);
        ImgCards[i]->Refresh();
      }
      cardsUsed[i]=0;
    }

    //Switch Get Rid of Some of Dealers Cards
    for (int i=0;i<5;i++) {
      int ncard=-1;
      if (i!=dealer.GetCardHand() && i!=dealer.HighestCard())
      dealer.SetCard(i,deck.NextCard());
    }

    //Show Dealers Cards
    for (int i=0;i<5;i++) {
      int ncard = dealer.GetCard(i);
      Cards->GetBitmap(ncard,ImgCards[i+5]->Picture->Bitmap);
      ImgCards[i+5]->Refresh();
    }

    //Determine who wins
    String p1hand = player.NameOfHand(player.GetHandType());
    String p2hand = dealer.NameOfHand(dealer.GetHandType());
    String win;
    String hcard1,hcard2;

    //Determine highest card
    int h1,h2;
    h1 = player.HighestCard();
    h2 = dealer.HighestCard();

    if (h1==14)h1=1;
    if (h2==14)h2=1;

    hcard1 = (String)deck.GetFace(h1)+" High";
    hcard2 = (String)deck.GetFace(h2)+" High";

    //Set win statement to highest card
    if (player.GetHandType()>dealer.GetHandType()) {
      win = "You Win!";
    } else if (player.GetHandType()<dealer.GetHandType()) {
      win = "Dealer Wins...";
    } else {
      if (player.GetCardHand()>dealer.GetCardHand()) {
        win = "You Win!";
      } else if (player.GetCardHand()<dealer.GetCardHand()) {
        win = "Dealer Wins...";
      } else {
        for (int i=0;i<5;i++) {
          if (player.HighestCard(i)>dealer.HighestCard(i)) {
            win = "You Win!"; break;
          } else if (player.HighestCard(i)<dealer.HighestCard(i)) {
            win = "Dealer Wins..."; break;
          } else {
            win = "You Both Tied...";
          }
        }
      }
    }

    if (win=="You Win!") player.AddWin();
    if (win=="Dealer Wins...") dealer.AddWin();

    Steps = "You had\n"+p1hand+", "+hcard1+"\n\nDealer Had\n"+p2hand+", "+hcard2+"\n\n"+win+"\n\nClick the deck to play again!";
  } else if (stage==1) { //Reset
    deck.Shuffle(120);   //Shuffle the Deck
    player.ClearCards(); //Reset Players Cards
    dealer.ClearCards(); //Reset Dealers Cards

    for (int i=0;i<10;i++) {
      Cards->GetBitmap(0,ImgCards[i]->Picture->Bitmap);
      ImgCards[i]->Refresh();
    }

    //Deal Players Hand
    for (int i=0;i<5;i++) {
      player.SetCard(i,deck.NextCard());
      int ncard = player.GetCard(i);
      Cards->GetBitmap(ncard,ImgCards[i]->Picture->Bitmap);
      ImgCards[i]->Refresh();
    }

    //Deal Computers Hand
    for (int i=0;i<5;i++) {
      dealer.SetCard(i,deck.NextCard());
    }

    stage = 0;

    Steps = "Choose cards you want to \ndiscard\n\nThen click on the deck when\nyou are done";
  }
}
//---------------------------------------------------------------------------
