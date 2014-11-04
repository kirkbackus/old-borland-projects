//---------------------------------------------------------------------------

#ifndef pokerH
#define pokerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>

//---------------------------------------------------------------------------
//Player Class
class Player {
  public:

  Player() {
  }

  Player(int player_type) {
  }

  void SetCard(int index, int card) {
    card++;
    cards[index]=card;
  }

  int GetCard(int index) {
    return(cards[index]);
  }

  int GetHandType() {
    int tc[5],ts[5];
    for (int i=0;i<5;i++)ts[i]=GetIntSuit(cards[i]);
    for (int i=0;i<5;i++)tc[i]=GetIntFace(cards[i]);
    int n = 5;
    for(int x=0; x<n; x++) {
      for(int y=0; y<n-1; y++) {
        if(tc[y]<tc[y+1]) {
          int tsuit = ts[y+1];
   	  int temp = tc[y+1];
          ts[y+1] = ts[y];
   	  tc[y+1] = tc[y];
          ts[y] = tsuit;
	  tc[y] = temp;
        }
      }
    }

    if (ts[0]==ts[1] && ts[1]==ts[2] && ts[2]==ts[3] && ts[3]==ts[4]) {
      if (tc[0]==12 && tc[1]==11 && tc[2]==10 && tc[3]==9 && tc[4]==0)
        return (9); //Royal Flush
      else if (tc[0]==tc[1]+1 && tc[1]==tc[2]+1 && tc[2]==tc[3]+1 && tc[3]==tc[4]+1)
        return (8); //Straight Flush
      else if (tc[0]==tc[1] && tc[1]==tc[2] && tc[2]==tc[3] || tc[1]==tc[2] &&
        tc[2]==tc[3] && tc[3]==tc[4]) return (7); //4 of a Kind
      else if (tc[0]==tc[1] && tc[1]==tc[2] && tc[3]==tc[4] || tc[0]==tc[1] &&
        tc[2]==tc[3] && tc[3]==tc[4]) return(6); //Full House
      else return (5); //Flush
    } else if (tc[0]==tc[1] && tc[1]==tc[2] && tc[2]==tc[3] || tc[1]==tc[2] &&
    tc[2]==tc[3] && tc[3]==tc[4]) return (7); //4 of a Kind
    else if (tc[0]==tc[1] && tc[1]==tc[2] && tc[3]==tc[4] || tc[0]==tc[1] &&
    tc[2]==tc[3] && tc[3]==tc[4]) return(6); //Full House
    else if (tc[0]==tc[1]+1 && tc[1]==tc[2]+1 && tc[2]==tc[3]+1 && tc[3]==tc[4]+1) return (4); //Straight
    else if (tc[0]==tc[1] && tc[1]==tc[2] || tc[1]==tc[2] && tc[2]==tc[3] ||
    tc[2]==tc[3] && tc[3]==tc[4]) return (3); //Three of a kind
    else if (tc[0]==tc[1] && tc[2]==tc[3] || tc[1]==tc[2] && tc[3]==tc[4] ||
    tc[0]==tc[1] && tc[3]==tc[4])
    return (2); //Two Pair
    else if (tc[0]==tc[1] || tc[1]==tc[2] || tc[2]==tc[3] || tc[3]==tc[4])
    return (1); //2 of a Kind
    else return (0); //Nothing, you suck
  }

  String NameOfHand(int hand) {
    if (hand==0) return ("Nothing");
    if (hand==1) return ("2 of a Kind");
    if (hand==2) return ("2 Pair");
    if (hand==3) return ("3 of a Kind");
    if (hand==4) return ("Straight");
    if (hand==5) return ("Flush");
    if (hand==6) return ("Full House");
    if (hand==7) return ("4 of a Kind");
    if (hand==8) return ("Straight Flush");
    if (hand==9) return ("Royal Flush");
    return 0;
  }

  int HighestCard() {
    int tmpcards[5];
    int n=5;

    for (int i=0;i<5;i++) {
      tmpcards[i]=GetIntFace(cards[i])+1;
      if (tmpcards[i]==1)tmpcards[i]+=13;//If it is an ace, make it highest card
    }

    for(int x=0; x<n; x++) {
      for(int y=0; y<n-1; y++) {
        if(tmpcards[y]<tmpcards[y+1]) {
   	  int temp = tmpcards[y+1];
   	  tmpcards[y+1] = tmpcards[y];
	  tmpcards[y] = temp;
        }
      }
    }
    return (tmpcards[0]);
  }

  int HighestCard(int index_of_highest) {
    int tmpcards[5];
    int n=5;

    for (int i=0;i<5;i++) {
      tmpcards[i]=GetIntFace(cards[i])+1;
      if (tmpcards[i]==1)tmpcards[i]+=13;//If it is an ace, make it highest card
    }

    for(int x=0; x<n; x++) {
      for(int y=0; y<n-1; y++) {
        if(tmpcards[y]<tmpcards[y+1]) {
   	  int temp = tmpcards[y+1];
   	  tmpcards[y+1] = tmpcards[y];
	  tmpcards[y] = temp;
        }
      }
    }
    return (tmpcards[index_of_highest]);
  }


  void ClearCards() {
    for (int i=0;i<5;i++)cards[i]=0;
  }

  int GetWins() {
    return (wins);
  }

  void AddWin() {
    wins++;
  }

  int GetCardHand() {
    int tc[5];
    int n=5;

    for (int i=0;i<5;i++) {
      tc[i]=GetIntFace(cards[i])+1;
      if (tc[i]==1)tc[i]+=13;//If it is an ace, make it highest card
    }

    for(int x=0; x<n; x++) {
      for(int y=0; y<n-1; y++) {
        if(tc[y]<tc[y+1]) {
   	  int temp = tc[y+1];
   	  tc[y+1] = tc[y];
	  tc[y] = temp;
        }
      }
    }

    int hand = GetHandType();
    int same=-1,high=-1;
    if (hand==1 || hand==2 || hand==3 || hand==6 || hand==7) {
      for (int i=0;i<5;i++) {
        if (tc[i]==same && high <= same) high=same;
        same = tc[i];
      }
    }
    return (high);
  }

  private:

  int type;
  int cards[5];
  int wins;

  int GetIntSuit(int card) {
    int _suit=(int)(card-1)/13;
    return (_suit);
  }

  int GetIntFace(int card) {
    int _face=(card-1)%13;
    return (_face);
  }
};

class Deck {
  public:

  Deck() {
    for (int i=0;i<52;i++)deck[i]=i;
    suit[0]="Clubs";
    suit[1]="Diamonds";
    suit[2]="Hearts";
    suit[3]="Spades";
    face[0]="Ace";
    face[1]="Deuce";
    face[2]="Three";
    face[3]="Four";
    face[4]="Five";
    face[5]="Six";
    face[6]="Seven";
    face[7]="Eight";
    face[8]="Nine";
    face[9]="Ten";
    face[10]="Jack";
    face[11]="Queen";
    face[12]="King";
  }

  const char* GetSuit(int card) {
    card--;
    int _suit=(int)card/13;
    return suit[_suit];
  }

  const char* GetFace(int card) {
    card--;
    int _face=card%13;
    return face[_face];
  }

  void Shuffle(int iterations) {
    int itr=iterations;
    for (int i=0;i<itr;i++) {
      int card1 = rand()%52;
      int card2 = rand()%52;
      int tmp = deck[card1];
      deck[card1]=deck[card2];
      deck[card2]=tmp;
    }
  }

  int NextCard() {
    int card = deck[0];
    for (int i=0;i<51;i++) deck[i]=deck[i+1];
    deck[51]=card;
    return (card);
  }

  int CurrentCard() {
    return(deck[51]);
  }

  private:

  const char *suit[4];
  const char *face[13];
  int deck[52];
};

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *GameTimer;
        TShape *TitleBar;
        TLabel *Title;
        TPanel *Quit;
        TBevel *TitleBevel;
        TImageList *Cards;
        TImage *PCard1;
        TImage *PCard2;
        TImage *PCard3;
        TImage *PCard4;
        TImage *PCard5;
        TGroupBox *PlayerHand;
        TShape *PSelect;
        TGroupBox *CompBox1;
        TImage *CCard1;
        TImage *CCard2;
        TImage *CCard3;
        TImage *CCard4;
        TImage *CCard5;
        TGroupBox *Results;
        TLabel *GameInfo;
        TBevel *Bevel1;
        TImage *Card1;
        TLabel *LWins;
        TBevel *Bevel2;
        TLabel *LSteps;
        TGroupBox *DeckBox;
        void __fastcall GameTimerTimer(TObject *Sender);
        void __fastcall QuitClick(TObject *Sender);
        void __fastcall TitleBarMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Card1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
