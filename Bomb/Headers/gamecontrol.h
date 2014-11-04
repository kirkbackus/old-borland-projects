#ifndef __GAMECONTROL_H
#define __GAMECONTROL_H

#define PORT 1423

class GameControl {
    public:

    bool host;
    float started;
    char name[25];

    int maxkills;
    int numplayers;

    int pid;

    char* ipaddr;

    bool sent_join;

    glFont* font;

    ServerSocket* s;
    ClientSocket* c;

    Player* p[4];
    int sockid[4];
    int timeout[4];

    int kills[4], deaths[4];
    char names[25][4];

    GameControl(HDC dc, Player* p1, Player* p2, Player* p3, Player* p4);

    bool HostGame();
    bool JoinGame(char* ip);

    void Update();
    void HostUpdate();
    void ClientUpdate();

    void AddKill(int playerid);
    void AddDeath(int playerid);
    void Shoot();

    Player* SetControl() { if (pid==-1) return NULL; else return(p[pid]); }

    void Draw();
};

GameControl::GameControl(HDC dc, Player* p1, Player* p2, Player* p3, Player* p4) {
    started = 0;
    host = 0;
    maxkills = 0;
    numplayers = 0;

    for (int i=0;i<4;i++) {
        kills[i] = 0;
        deaths[i] = 0;
    }

    sprintf(name,"Player %i",rand()%1000+1);

    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;

    s = NULL;
    c = NULL;

    pid = -1;
    sent_join = 0;

    font = new glFont(dc,"Arial",32);
    Init39();
}

bool GameControl::HostGame() {
    if (s!=NULL) { delete s; s = NULL; }
    if (c!=NULL) { delete c; c = NULL; }

    s = new ServerSocket();

    if (s->Listen(PORT,1)) {
        sockid[0] = 0;
        host = 1;
        maxkills = 15;
        numplayers = 1;
        started = 1;
        pid = 0;
        sprintf(names[0],"%s",name);
        p[pid]->control = 1;
        ipaddr = s->GetIPAddress();

        return 1;
    } else {
        delete s;
        s = NULL;
        return 0;
    }
}

bool GameControl::JoinGame(char* ip) {
    if (s!=NULL) { delete s; s = NULL; }
    if (c!=NULL) { delete c; c = NULL; }

    c = new ClientSocket();

    if (c->Connect(ip,PORT)!=-1) {
        host = 0;
        started = 1;
        ipaddr = c->GetIPAddress();
        return 1;
    } else {
        delete c;
        c = NULL;
        return 0;
    }
}

void GameControl::Update() {
    if (started) {
        if (host) HostUpdate();
        else ClientUpdate();
    }
}

void GameControl::HostUpdate() {
    int newid = s->Accept();
    if (newid) { //HEY A NEW PLAYER!!
        numplayers++;

        setnagle(newid,0);

        byte nid;
        for (int i=0;i<4;i++) {
            if (!p[i]->visible) {
                nid=i;
                p[nid]->Activate(1);
                break;
            } else if (i==3) {
                closesocket(newid);
                return;
            }
        }

        //Send Client's New info
        s->ResetBuffer();
        s->WriteByte(1);
        s->WriteInt(maxkills);
        s->WriteInt(numplayers);
        s->WriteByte(nid);

        s->WriteByte(p[0]->visible);
        s->WriteByte(p[1]->visible);
        s->WriteByte(p[2]->visible);
        s->WriteByte(p[3]->visible);

        s->WriteByte(kills[0]);
        s->WriteByte(kills[1]);
        s->WriteByte(kills[2]);
        s->WriteByte(kills[3]);

        s->WriteByte(deaths[0]);
        s->WriteByte(deaths[1]);
        s->WriteByte(deaths[2]);
        s->WriteByte(deaths[3]);

        s->Send(newid);

        //Let other players know of new guy
        s->ResetBuffer();
        s->WriteByte(2);
        s->WriteByte(nid);
        s->Send();
    }

    int connid = 0;
    while(1) {
        int size = s->Receive(connid);

        if (size<0) {
            connid++;
            if (connid>s->GetNumConnections()) break;
            else continue;
        }

        if (size==0) { ///THIS MEANS THE PLAYER LEFT SO WE WILL KILL HIM
            //OH WELL
        }

        if (size>0) { ///LOOK THROUGH ALL THE MESSAGES
            int msgid = (int)s->ReadByte(); //Get's the ID of the message

            switch (msgid) {
                int cid;
                case 0: ///UPDATE CLIENT POSITIONS & STUFF

                cid = (int)s->ReadByte();

                p[cid]->x = s->ReadFloat();
                p[cid]->y = s->ReadFloat();
                p[cid]->aimdir = s->ReadFloat();
                p[cid]->health = s->ReadInt();

                break;

                case 1: ///UPDATE SOMEBODY'S NAME

                cid = (int)s->ReadByte();
                sprintf(names[cid],"%s",s->ReadString());

                s->ResetBuffer();
                s->WriteByte(5);
                s->WriteStruct(names[0]);
                s->WriteStruct(names[1]);
                s->WriteStruct(names[2]);
                s->WriteStruct(names[3]);
                s->Send();

                break;

                case 2: ///SOMEBODY SHOT A BULLET

                cid = (int)s->ReadByte();
                p[cid]->weapon->Change(s->ReadByte());
                p[cid]->x = s->ReadFloat();
                p[cid]->y = s->ReadFloat();
                p[cid]->aimdir = s->ReadFloat();
                p[cid]->Shoot();

                ///TELL OTHER PLAYERS THAT THIS PERSON SHOT
                s->ResetBuffer();
                s->WriteByte(3);
                s->WriteByte(cid);
                s->WriteByte(p[cid]->weapon->type);
                s->WriteFloat(p[cid]->x);
                s->WriteFloat(p[cid]->y);
                s->WriteFloat(p[cid]->aimdir);
                s->Send();

                break;

                case 4: ///UPDATE SCORE

                cid = s->ReadByte();
                byte sd = s->ReadByte();
                if (sd==0) AddDeath(cid);
                if (sd==1) AddKill(cid);

                break;
            }
        }
    }

    //UPDATES ALL POSITIONS FOR ALL PLAYERS
    for (int i=0;i<4;i++) {
        s->ResetBuffer();
        s->WriteByte(0);
        s->WriteByte(i);
        s->WriteFloat(p[i]->x);
        s->WriteFloat(p[i]->y);
        s->WriteFloat(p[i]->aimdir);
        s->WriteFloat(p[i]->health);
        s->Send();
    }
}

void GameControl::ClientUpdate() {
    if (pid!=-1) { //TELL SERVER WHERE YOU ARE
        c->ResetBuffer();
        c->WriteByte(0);
        c->WriteByte(pid);
        c->WriteFloat(p[pid]->x);
        c->WriteFloat(p[pid]->y);
        c->WriteFloat(p[pid]->aimdir);
        c->WriteInt((int)p[pid]->health);
        c->Send();
    }

    while(1) {
        int size = c->Receive();

        if (size<0) break;

        if (size==0) { //THIS MEANS THE PLAYER LEFT SO WE WILL END THE GAME
            started = 0;
            break;
        }

        int msgid = (int)readbyte(0); //Get's the ID of the message

        switch (msgid) {
            case 0: //Update a player's position

            byte cid = (byte)c->ReadByte();
            if (cid==pid) {
                c->ResetBuffer();
                break;
            }
            p[cid]->x = c->ReadFloat();
            p[cid]->y = c->ReadFloat();
            p[cid]->aimdir = c->ReadFloat();
            p[cid]->health = c->ReadInt();

            break;

            case 1: ///Server Affirms you joining so let's get some info

            if (pid==-1) {
                maxkills = c->ReadInt();
                numplayers = c->ReadInt();
                pid = c->ReadByte();

                p[0]->Activate(c->ReadByte());
                p[1]->Activate(c->ReadByte());
                p[2]->Activate(c->ReadByte());
                p[3]->Activate(c->ReadByte());

                kills[0] = c->ReadByte();
                kills[1] = c->ReadByte();
                kills[2] = c->ReadByte();
                kills[3] = c->ReadByte();

                deaths[0] = c->ReadByte();
                deaths[1] = c->ReadByte();
                deaths[2] = c->ReadByte();
                deaths[3] = c->ReadByte();

                p[pid]->Activate(1);
                p[pid]->control = 1;

                //Send Server your name
                c->ResetBuffer();
                c->WriteByte(1);
                c->WriteByte(pid);
                c->WriteStruct(name);
                c->Send();
            }

            break;

            case 2: ///Another dude joined

            int tnid = c->ReadByte();
            if (tnid==pid) break;
            numplayers++;
            p[tnid]->Activate(1);

            break;

            case 3: ///Some Guy Shot

            cid = (int)c->ReadByte();
            if (cid == pid) break;
            p[cid]->weapon->Change(c->ReadByte());
            p[cid]->x = c->ReadFloat();
            p[cid]->y = c->ReadFloat();
            p[cid]->aimdir = c->ReadFloat();
            p[cid]->Shoot();

            break;

            case 4: ///Update Score

            byte sd = c->ReadByte();
            cid = c->ReadByte();
            if (sd==0) deaths[cid] = c->ReadByte();
            if (sd==1) kills[cid] = c->ReadByte();

            break;

            case 5: ///Update Names

            c->ReadStruct(names[0],25);
            c->ReadStruct(names[1],25);
            c->ReadStruct(names[2],25);
            c->ReadStruct(names[3],25);

            break;
        }
    }
}

void GameControl::Shoot() {
    if (host) {
        s->ResetBuffer();
        s->WriteByte(3);
        s->WriteByte(pid);
        s->WriteByte(p[pid]->weapon->type);
        s->WriteFloat(p[pid]->x);
        s->WriteFloat(p[pid]->y);
        s->WriteFloat(p[pid]->aimdir);
        s->Send();
    } else {
        c->ResetBuffer();
        c->WriteByte(2);
        c->WriteByte(pid);
        c->WriteByte(p[pid]->weapon->type);
        c->WriteFloat(p[pid]->x);
        c->WriteFloat(p[pid]->y);
        c->WriteFloat(p[pid]->aimdir);
        c->Send();
    }
}

void GameControl::AddKill(int playerid) {
    if (host) {
        kills[playerid]++;
        s->ResetBuffer();
        s->WriteByte(4);
        s->WriteByte(1); //Score Change - Kill
        s->WriteByte(playerid);
        s->WriteByte(kills[playerid]);
        s->Send();
    } else {
        c->ResetBuffer();
        c->WriteByte(4);
        c->WriteByte(playerid);
        c->WriteByte(1); //Score Change - Kill
        c->Send();
    }
}

void GameControl::AddDeath(int playerid) {
    if (host) {
        deaths[playerid]++;
        s->ResetBuffer();
        s->WriteByte(4);
        s->WriteByte(0); //Score Change - Death
        s->WriteByte(playerid);
        s->WriteByte(deaths[playerid]);
        s->Send();
    } else {
        c->ResetBuffer();
        c->WriteByte(4);
        c->WriteByte(playerid);
        c->WriteByte(0); //Score Change - Death
        c->Send();
    }
}

void GameControl::Draw() {
    if (started) {
        if (GetAsyncKeyState(VK_SHIFT)) {
            DrawRectangle(32,32,608,448,1,1,1,.8,0);
            DrawRectangle(32,32,608,448,1,1,1,1,1);
            DrawRectangle(64,64,576,416,0,0,0,.8,0);
            DrawRectangle(64,64,576,416,0,0,0,1,1);

            glBegin(GL_QUADS);

            glColor4f(1,1,1,.5);

            glVertex2f(65,108);
            glVertex2f(575,108);

            glColor4f(1,1,1,0);

            glVertex2f(575,576);
            glVertex2f(65,576);

            glEnd();

            glColor4f(1,1,1,1);

            DrawLine(65,108,575,108,1,1,1,1);
            font->glPrint(69,69,FA_LEFT,"Player");
            font->glPrint(571,69,FA_RIGHT,"Kills   Deaths");

            for (int i=0;i<4;i++) {
                if (!p[i]->visible) continue;
                font->glPrint(69,69+(i+1)*48,FA_LEFT,"%s",names[i]);
                font->glPrint(576-155,69+(i+1)*48,FA_CENTER,"%i",kills[i]);
                font->glPrint(576-60,69+(i+1)*48,FA_CENTER,"%i",deaths[i]);
            }

            glColor4f(0,0,0,1);
            font->glPrint(320,410,FA_CENTER,"Local IP: %s",ipaddr);
        }
    }
}

#endif
