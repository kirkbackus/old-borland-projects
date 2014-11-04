struct MenuItem {
    int x,y,arg,type;
    char text[128];
};

class Menu {
    private:

    char* title;
    vector<MenuItem*> items;
    vector<std::string*> edititems;

    glFont* tfont;
    glFont* font;
    int sleep;

    public:

    bool visible;
    bool vprev;
    int selected;

    Menu(HDC dc);
    ~Menu();

    void SetTitle(char* new_title) { title = new_title; }
    void AddItem(char* name);
    void AddItem(char* name, int t);
    int ItemSelected();
    string GetStringSelected(int id) { return (*edititems[id]); }

    void Update();
    void Draw();
};

Menu::Menu(HDC dc) {
    tfont = new glFont(dc, "Arial",48);
    font = new glFont(dc, "Arial",32);
    visible = 1;
    selected = 0;
    sleep = 0;
}

void Menu::AddItem(char* name) {
    items.push_back(new MenuItem());
    items[items.size()-1]->x = 320;
    items[items.size()-1]->y = 128+(items.size()+1)*32;
    sprintf(items[items.size()-1]->text,"%s",name);
    items[items.size()-1]->type = 0;
    edititems.push_back(new std::string(""));
}

void Menu::AddItem(char* name, int t) {
    items.push_back(new MenuItem());
    items[items.size()-1]->x = 320;
    items[items.size()-1]->y = 128+(items.size()+1)*32;
    sprintf(items[items.size()-1]->text,"%s",name);
    items[items.size()-1]->type = t;
    edititems.push_back(new std::string(""));
}

int Menu::ItemSelected() {
    if (!visible) return(-1);
    if (KeyJustPressed(VK_RETURN) && visible==vprev) {
        return(selected);
    } else return(-1);
}

void Menu::Update() {
    vprev = visible;
    if (!visible) return;

    if (KeyJustPressed(VK_UP)) {
        selected--;
        if (selected<0) selected = items.size()-1;
    }

    if (KeyJustPressed(VK_DOWN)) {
        selected++;
        if (selected>items.size()-1) selected = 0;
        sleep = 10;
    }

    if (items[selected]->type==1) {
        for (int i=48;i<=58;i++) {
            if (i==58) i = 190;
            char t[2];
            if (i<58)sprintf(t,"%c",(char)i);
            else sprintf(t,"%c",'.');
            if (KeyJustPressed(i)) edititems[selected]->append(t);
        }

        if (sleep>0)sleep--;

        if (GetAsyncKeyState(VK_BACK)) {
            if (edititems[selected]->length()>0 && sleep==0) {
                edititems[selected]->erase(edititems[selected]->end()-1);
                sleep=20;
            }
        }
    }

    if (items[selected]->type==2) {
        for (int i=65;i<=90;i++) {
            char t[2];
            sprintf(t,"%c",(char)(i+!KeyPressed(VK_SHIFT)*32));
            if (KeyJustPressed(i)) edititems[selected]->append(t);
        }

        if (sleep>0)sleep--;

        if (GetAsyncKeyState(VK_BACK)) {
            if (edititems[selected]->length()>0 && sleep==0) {
                edititems[selected]->erase(edititems[selected]->end()-1);
                sleep=20;
            }
        }
    }
}

void Menu::Draw() {
    if (!visible) return;
    glColor4f(1,1,1,1);
    tfont->glPrint(320,128,FA_CENTER,title);
    for (int i=0;i<items.size();i++) {
        if (i==selected) glColor4f(1,1,0,1);
        else glColor4f(1,1,1,1);

        if (items[i]->type==0) font->glPrint(items[i]->x,items[i]->y,FA_CENTER,items[i]->text);
        if (items[i]->type==1) font->glPrint(items[i]->x,items[i]->y,FA_CENTER,"%s%s",items[i]->text,edititems[i]->c_str());
        if (items[i]->type==2) font->glPrint(items[i]->x,items[i]->y,FA_CENTER,"%s%s",items[i]->text,edititems[i]->c_str());
    }
}
