//<!-- 2-player version of Slime Volleyball -->
// Original code: Quin Pendragon, 1999.
//  I know that this isn't exactly an ideal example of either game coding or
//  good use of java. It wasn't meant to be. :P
//  No responsibility is taken for any damage to software, hardware,
//  keyboards, or individuals' coding habits as a result of using this code.
// Mods:
// 0) fractoid: Lost the source code, and decompiled the applet on my page
//    to get it back. This is why some of the methods are in a funny
//    order, and some variables are interestingly named :P
// 1) fractoid: added SuperSlime mod.
// 2) Kirk: added SuperSlime mode by pressing 'F'
// 3) Kirk: added Double Buffer ^_^
// 4) Kirk: added Beach Ball w/ less gravity
// ...

import java.applet.Applet;
import java.awt.*;

public class BeachSlime2P extends Applet
    implements Runnable
{
    private Color sky = new Color(64,128,255);
    private Color ground = new Color(255,255,128);
    private int nWidth;
    private int nHeight;
    private final int topScore = 10;
    private int nScore;
    private int nPointsScored;
    private int p1X;
    private int p2X;
    private int p1Y;
    private int p2Y;
    private int p1Col;
    private int p2Col;
    private Color slimeColours[];
    private String slimeColText[] = {
        "Big Red Slime ", "Magic Green Slime ", "Golden Boy ", "The Great White Slime ", "The Black Master Slime ", "The Invisible Blue Slime "
    };
    private int p1OldX;
    private int p2OldX;
    private int p1OldY;
    private int p2OldY;
    private int p1XV;
    private int p2XV;
    private int p1YV;
    private int p2YV;
    private int ballX;
    private int ballY;
    private int ballVX;
    private float ballVY;
    private int ballRad;
    private int ballOldX;
    private int ballOldY;
    private Graphics screen;
    private Image buffer;
    private boolean buffered;
    private String promptMsg;
    private int replayData[][];
    private int replayPos;
    private int replayStart;
    private boolean mousePressed;
    private boolean fCanChangeCol;
    private boolean fInPlay;
    private int p1Blink;
    private int p2Blink;
    private boolean fP1Touched;
    private boolean fP2Touched;
    private Thread gameThread;
    private boolean fEndGame;
    private long startTime;
    private long gameTime;
    private int scoringRun;
    private int frenzyCol1 = 2;
    private int frenzyCol2 = 0;
    private int ang=0;
    private int scoringRunForSuper = 3;

    public boolean handleEvent(Event event)
    {
        label0:
        switch(event.id)
        {
        default:
            break;

        case 503: // Event.MOUSE_MOVE
            showStatus("Slime Volleyball 2-Player, by Quin Pendragon: tartarus.uwa.edu.au/~fractoid, Modded by Kirk Backus");
            break;

        case 501: // Event.MOUSE_DOWN
            mousePressed = true;
            if(!fInPlay)
            {
                fEndGame = false;
                fInPlay = true;
                nScore = 5;
                nPointsScored = 0;
                p1X = 200;
                p1Y = 0;
                p2X = 800;
                p2Y = 0;
                p1XV = 0;
                p1YV = 0;
                p2XV = 0;
                p2YV = 0;
                ballX = 200;
                ballY = 400;
                ballVX = 0;
                ballVY = 0;
                promptMsg = "";
                repaint();
                gameThread = new Thread(this);
                gameThread.start();
            }
            break;

        case Event.KEY_ACTION:

        case 401: // Event.KEY_PRESS           
            switch (event.key)
            {
            default:
                break;
                
            case 70: // 'F'
            case 102: // 'f'      
                scoringRunForSuper = (scoringRunForSuper==3) ? -10 : 3;
                  
                break label0;
                
            case 66: // 'B'
            case 98: // 'b'
                buffered = !buffered;
                screen = buffered ? buffer.getGraphics() : getGraphics();
                screen.setFont(new Font(screen.getFont().getName(), 1, 16));
                repaint();
                break label0;           
            }
           
            if(fEndGame)
                break;
            switch(event.key)
            {
            default:
                break;

            case 65: // 'A'
            case 97: // 'a'
                p1XV = (scoringRun <= -scoringRunForSuper) ? -16 : -8;
                break label0;

            case 68: // 'D'
            case 100: // 'd'
                p1XV = (scoringRun <= -scoringRunForSuper) ? 16 : 8;
                break label0;

            case 87: // 'W'
            case 119: // 'w'
                if(p1Y == 0)
                    p1YV = (scoringRun <= -scoringRunForSuper) ? 45 : 31;
                break label0;

            case Event.LEFT:
            case 74: // 'J'
            case 106: // 'j'
                p2XV = (scoringRun >= scoringRunForSuper) ? -16 : -8;
                break label0;

            case Event.RIGHT:
            case 76: // 'L'
            case 108: // 'l'
                p2XV = (scoringRun >= scoringRunForSuper) ? 16 : 8;
                break label0;

            case Event.UP:
            case 73: // 'I'
            case 105: // 'i'
                if(p2Y == 0)
                    p2YV = (scoringRun >= scoringRunForSuper) ? 45 : 31;
                break label0;

            case 83: // 'S'
            case 115: // 's'
                if(!fCanChangeCol)
                    break label0;
                do
                    p1Col = p1Col != 5 ? p1Col + 1 : 0;
                while(p1Col == p2Col);
                drawScores();
                break label0;

            case Event.DOWN:
            case 75: // 'K'
            case 107: // 'k'
                if(fCanChangeCol)
                {
                    do p2Col = p2Col != 5 ? p2Col + 1 : 0;
                    while(p2Col == p1Col);
                    drawScores();
                    break label0;
                }
                // fall through

            case 32: // ' '
                mousePressed = true;
                break;
            }
            break;

        case Event.KEY_ACTION_RELEASE:
        
        case 402: // Event.KEY_RELEASE
            switch(event.key)
            {
            default:
                break label0;

            case 65: // 'A'
            case 97: // 'a'
                if(p1XV < 0)
                    p1XV = 0;
                break label0;

            case 68: // 'D'
            case 100: // 'd'
                if(p1XV > 0)
                    p1XV = 0;
                break label0;

            case Event.LEFT:
            case 74: // 'J'
            case 106: // 'j'
                if(p2XV < 0)
                    p2XV = 0;
                break label0;

            case Event.RIGHT:
            case 76: // 'L'
            case 108: // 'l'
                break;
            }
            if(p2XV > 0)
                p2XV = 0;
            break;
        }
        return false;
    }

    private void DrawSlimers()
    {
        int k1 = nWidth / 10;
        int j2 = nHeight / 10;
        int i3 = nWidth / 50;
        int j3 = nHeight / 25;
        int k3 = (ballX * nWidth) / 1000;
        int l3 = (4 * nHeight) / 5 - (ballY * nHeight) / 1000;
        int i = (p1OldX * nWidth) / 1000 - k1 / 2;
        int l = (7 * nHeight) / 10 - (p1OldY * nHeight) / 1000;
        screen.setColor(sky);
        screen.fillRect(i, l, k1, j2);
        i = (p2OldX * nWidth) / 1000 - k1 / 2;
        l = (7 * nHeight) / 10 - (p2OldY * nHeight) / 1000;
        screen.setColor(sky);
        screen.fillRect(i, l, k1, j2);
        MoveBall();
        i = (p1X * nWidth) / 1000 - k1 / 2;
        l = (7 * nHeight) / 10 - (p1Y * nHeight) / 1000;
        screen.setColor((scoringRun <= -scoringRunForSuper) ? slimeColours[frenzyCol1 = ((frenzyCol1 + 1) % slimeColours.length)] : slimeColours[p1Col]);
        screen.fillArc(i, l, k1, 2 * j2, 0, 180);
        int l4 = p1X + 38;
        int i5 = p1Y - 60;
        i = (l4 * nWidth) / 1000;
        l = (7 * nHeight) / 10 - (i5 * nHeight) / 1000;
        int i4 = i - k3;
        int j4 = l - l3;
        int k4 = (int)Math.sqrt(i4 * i4 + j4 * j4);
        boolean flag = Math.random() < 0.01D;
        if(flag)
            p1Blink = 5;
        if(p1Blink == 0)
        {
            screen.setColor(Color.white);
            screen.fillOval(i - i3, l - j3, i3, j3);
            if(k4 > 0 && !flag)
            {
                screen.setColor(Color.black);
                screen.fillOval(i - (4 * i4) / k4 - (3 * i3) / 4, l - (4 * j4) / k4 - (3 * j3) / 4, i3 / 2, j3 / 2);
            }
        } else
        {
            p1Blink--;
        }
        i = (p2X * nWidth) / 1000 - k1 / 2;
        l = (7 * nHeight) / 10 - (p2Y * nHeight) / 1000;
        screen.setColor((scoringRun >= scoringRunForSuper) ? slimeColours[frenzyCol2 = ((frenzyCol2 + 1) % slimeColours.length)] : slimeColours[p2Col]);
        screen.fillArc(i, l, k1, 2 * j2, 0, 180);
        l4 = p2X - 18;
        i5 = p2Y - 60;
        i = (l4 * nWidth) / 1000;
        l = (7 * nHeight) / 10 - (i5 * nHeight) / 1000;
        i4 = i - k3;
        j4 = l - l3;
        k4 = (int)Math.sqrt(i4 * i4 + j4 * j4);
        flag = Math.random() < 0.01D;
        if(flag)
            p2Blink = 5;
        if(p2Blink == 0)
        {
            screen.setColor(flag ? Color.gray : Color.white);
            screen.fillOval(i - i3, l - j3, i3, j3);
            if(k4 > 0 && !flag)
            {
                screen.setColor(Color.black);
                screen.fillOval(i - (4 * i4) / k4 - (3 * i3) / 4, l - (4 * j4) / k4 - (3 * j3) / 4, i3 / 2, j3 / 2);
            }
        } else
        {
            p2Blink--;
        }
        if(nScore > 8)
        {
            int j = (p1X * nWidth) / 1000;
            int i1 = (7 * nHeight) / 10 - ((p1Y - 40) * nHeight) / 1000;
            int l1 = nWidth / 20;
            int k2 = nHeight / 20;
            int j5 = 0;
            do
            {
                screen.setColor(Color.black);
                screen.drawArc(j, i1 + j5, l1, k2, -30, -150);
            } while(++j5 < 3);
            return;
        }
        if(nScore < 2)
        {
            int i2 = nWidth / 20;
            int l2 = nHeight / 20;
            int k = (p2X * nWidth) / 1000 - i2;
            int j1 = (7 * nHeight) / 10 - ((p2Y - 40) * nHeight) / 1000;
            int k5 = 0;
            do
            {
                screen.setColor(Color.black);
                screen.drawArc(k, j1 + k5, i2, l2, -10, -150);
            } while(++k5 < 3);
        }
    }

    public void paint(Graphics g)
    {
        g = buffered ? buffer.getGraphics() : screen;
        nWidth = size().width;
        nHeight = size().height;
        g.setColor(sky);
        g.fillRect(0, 0, nWidth, (4 * nHeight) / 5);
        g.setColor(ground);
        g.fillRect(0, (4 * nHeight) / 5, nWidth, nHeight / 5);
        g.setColor(Color.white);
        g.fillRect(nWidth / 2 - 2, (7 * nHeight) / 10, 4, nHeight / 10 + 5);
        drawScores();
        drawPrompt();
        if(!fInPlay)
        {
            FontMetrics fontmetrics = screen.getFontMetrics();
            screen.setColor(Color.white);
            screen.drawString("Slime Volleyball!", nWidth / 2 - fontmetrics.stringWidth("Slime Volleyball!") / 2, nHeight / 2 - fontmetrics.getHeight());
            g.setColor(Color.white);
            fontmetrics = g.getFontMetrics();
            g.drawString("Written by Quin Pendragon", nWidth / 2 - fontmetrics.stringWidth("Written by Quin Pendragon") / 2, nHeight / 2 + fontmetrics.getHeight() * 2);
            g.drawString("Modded by Kirk Backus", nWidth / 2 - fontmetrics.stringWidth("Modded by Kirk Backus") / 2, nHeight / 2 + fontmetrics.getHeight() * 2+16);
            g.drawString("Last Level Games (LLgames.net)", nWidth / 2 - fontmetrics.stringWidth("Last Level Games (LLgames.net)") / 2, nHeight / 2 + fontmetrics.getHeight() * 2+32);
        }
        if (buffered) getGraphics().drawImage(buffer, 0, 0, null);
    }

    public void destroy()
    {
        gameThread.stop();
        gameThread = null;
    }

    private void ReplayFrame(int i, int j, int k, int l, int i1, boolean flag)
    {
        if(flag)
        {
            ballX = ballOldX = 0xfd050f80;
            ballY = ballOldY = 0x186a0;
            p1OldX = p1OldY = p2OldX = p2OldY = -10000;
        } else
        {
            int j1 = i != 0 ? i - 1 : 199;
            p1OldX = replayData[j1][0];
            p1OldY = replayData[j1][1];
            p2OldX = replayData[j1][2];
            p2OldY = replayData[j1][3];
            ballOldX = replayData[j1][4];
            ballOldY = replayData[j1][5];
        }
        p1X = replayData[i][0];
        p1Y = replayData[i][1];
        p2X = replayData[i][2];
        p2Y = replayData[i][3];
        ballX = replayData[i][4];
        ballY = replayData[i][5];
        p1Col = replayData[i][6];
        p2Col = replayData[i][7];
        ballVX = 0;
        ballVY = 1;
        if((i / 10) % 2 > 0)
        {
            screen.setColor(Color.red);
            screen.drawString("Replay...", j, k);
        } else
        {
            screen.setColor(sky);
            screen.fillRect(j, k - i1, l, i1 * 2);
        }
        DrawSlimers();
        try
        {
            Thread.sleep(20L);
            return;
        }
        catch(InterruptedException _ex)
        {
            return;
        }
    }

    private String MakeTime(long l)
    {
        long l1 = (l / 10L) % 100L;
        long l2 = (l / 1000L) % 60L;
        long l3 = (l / 60000L) % 60L;
        long l4 = l / 0x36ee80L;
        String s = "";
        if(l4 < 10L)
            s += "0";
        s += l4;
        s += ":";
        if(l3 < 10L)
            s += "0";
        s += l3;
        s += ":";
        if(l2 < 10L)
            s += "0";
        s += l2;
        s += ":";
        if(l1 < 10L)
            s += "0";
        s += l1;
        return s;
    }

    private void MoveSlimers()
    {
        p1X += p1XV;
        if(p1X < 50)
            p1X = 50;
        if(p1X > 445)
            p1X = 445;
        if(p1YV != 0)
        {
            p1Y += p1YV -= (scoringRun <= -scoringRunForSuper) ? 4 : 2;
            if(p1Y < 0)
            {
                p1Y = 0;
                p1YV = 0;
            }
        }
        p2X += p2XV;
        if(p2X > 950)
            p2X = 950;
        if(p2X < 555)
            p2X = 555;
        if(p2YV != 0)
        {
            p2Y += p2YV -= (scoringRun >= scoringRunForSuper) ? 4 : 2;
            if(p2Y < 0)
            {
                p2Y = 0;
                p2YV = 0;
            }
        }
    }

    public BeachSlime2P()
    {
        //buffered=false;
        p2Col = 1;
        slimeColours = (new Color[] {
            Color.red, Color.green, Color.yellow, Color.white, Color.black, sky
        });
        replayData = new int[200][8];
    }

    private void MoveBall()
    {
        int k = ((ballRad+5) * nHeight) / 1000;
        int i = (ballOldX * nWidth) / 1000;
        int j = (4 * nHeight) / 5 - (ballOldY * nHeight) / 1000;
        screen.setColor(sky);
        screen.fillOval(i - k-2, j - k-2, k * 2+4, k * 2+4);
        ballY += ballVY-=.75;
        ballX += ballVX;
        ang-=ballVX;
        if (ang>360)ang-=360;
        if (ang<0)ang+=360;
        if(!fEndGame)
        {
            int l1 = (ballX - p1X) * 2;  //Change in X*2 Since it is twice as wide
            int i2 = ballY - p1Y;        //Change in Y
            int j2 = l1 * l1 + i2 * i2;  //Change in X Squared + Change in Y Squared
            int k2 = ballVX - p1XV;      //Change in Horiziontal Velocity
            int l2 = (int)ballVY - p1YV;      //Change in Vertical Velocity
            if(i2 > 0 && j2 < 15625 && j2 > 25) //Check if Collided
            {
                int l = (int)Math.sqrt(j2);         //Get The Distance from the ball to player
                int j1 = (l1 * k2 + i2 * l2) / l;   //Not sure what this is
                ballX = p1X + (l1 * (63)) / l;  //Keep Ball outside player (x)
                ballY = p1Y + (i2 * (125)) / l; //Keep Ball outside player (y)
                if(j1 <= 32)
                {
                    ballVX += p1XV - (2 * l1 * j1) / l;
                    if(ballVX < -15)
                        ballVX = -15;
                    if(ballVX > 15)
                        ballVX = 15;
                    ballVY += p1YV - (2 * i2 * j1) / l;
                    if(ballVY < -22)
                        ballVY = -22;
                    if(ballVY > 22)
                        ballVY = 22;
                }
                fP1Touched = true;
            }
            l1 = (ballX - p2X) * 2;
            i2 = ballY - p2Y;
            j2 = l1 * l1 + i2 * i2;
            k2 = ballVX - p2XV;
            l2 = (int)ballVY - p2YV;
            if(i2 > 0 && j2 < 15625 && j2 > 25)
            {
                int i1 = (int)Math.sqrt(j2);
                int k1 = (l1 * k2 + i2 * l2) / i1;
                ballX = p2X + (l1 * (63)) / i1;
                ballY = p2Y + (i2 * (125)) / i1;
                if(k1 <= 0)
                {
                    ballVX += p2XV - (2 * l1 * k1) / i1;
                    if(ballVX < -15)
                        ballVX = -15;
                    if(ballVX > 15)
                        ballVX = 15;
                    ballVY += p2YV - (2 * i2 * k1) / i1;
                    if(ballVY < -22)
                        ballVY = -22;
                    if(ballVY > 22)
                        ballVY = 22;
                }
                fP2Touched = true;
            }
            if(ballX < 15)
            {
                ballX = 15;
                ballVX = -ballVX;
            }
            if(ballX > 985)
            {
                ballX = 985;
                ballVX = -ballVX;
            }
            if(ballX > 480 && ballX < 520 && ballY < 140)
                if(ballVY < 0 && ballY > 130)
                {
                    ballVY *= -1;
                    ballY = 130;
                } else
                if(ballX < 500)
                {
                    ballX = 480;
                    ballVX = ballVX >= 0 ? -ballVX : ballVX;
                } else
                {
                    ballX = 520;
                    ballVX = ballVX <= 0 ? -ballVX : ballVX;
                }
        }
        i = (ballX * nWidth) / 1000;
        j = (4 * nHeight) / 5 - (ballY * nHeight) / 1000;
        
        screen.setColor(Color.yellow);
        screen.fillArc(i - k, j - k, k * 2, k * 2, ang, 90);
        screen.setColor(Color.green);
        screen.fillArc(i - k, j - k, k * 2, k * 2, ang+90, 90);
        screen.setColor(Color.pink);
        screen.fillArc(i - k, j - k, k * 2, k * 2, ang+180, 90);
        screen.setColor(Color.cyan);
        screen.fillArc(i - k, j - k, k * 2, k * 2, ang+270, 90);
        screen.setColor(Color.black);
        screen.drawArc(i - k, j - k, k * 2, k * 2, 0, 360);
    }

    private void DrawStatus()
    {
        Graphics g = screen;
        int i = nHeight / 20;
        g.setColor(sky);
        FontMetrics fontmetrics = screen.getFontMetrics();
        int j = nWidth / 2 + ((nScore - 5) * nWidth) / 24;
        String s = "Points: " + nPointsScored + "   Elapsed: " + MakeTime(gameTime);
        int k = fontmetrics.stringWidth(s);
        g.fillRect(j - k / 2 - 5, 0, k + 10, i + 22);
        g.setColor(Color.white);
        screen.drawString(s, j - k / 2, fontmetrics.getAscent() + 20);
    }

    public void drawPrompt()
    {
        screen.setColor(ground);
        screen.fillRect(0, (4 * nHeight) / 5 + 6, nWidth, nHeight / 5 - 10);
        drawPrompt(promptMsg, 0);
        if (buffered)getGraphics().drawImage(buffer,0,0,null);
    }

    public void drawPrompt(String s, int i)
    {
        FontMetrics fontmetrics = screen.getFontMetrics();
        screen.setColor(Color.black);
        screen.drawString(s, (nWidth - fontmetrics.stringWidth(s)) / 2, (nHeight * 4) / 5 + fontmetrics.getHeight() * (i + 1) + 10);
    }

    private void SaveReplayData()
    {
        replayData[replayPos][0] = p1X;
        replayData[replayPos][1] = p1Y;
        replayData[replayPos][2] = p2X;
        replayData[replayPos][3] = p2Y;
        replayData[replayPos][4] = ballX;
        replayData[replayPos][5] = ballY;
        replayData[replayPos][6] = p1Col;
        replayData[replayPos][7] = p2Col;
        replayPos++;
        if(replayPos >= 200)
            replayPos = 0;
        if(replayStart == replayPos)
            replayStart++;
        if(replayStart >= 200)
            replayStart = 0;
    }

    private void drawScores()
    {
        Graphics g = screen;
        int k = nHeight / 20;
        g.setColor(sky);
        g.fillRect(0, 0, nWidth, k + 22);
        for(int l = 0; l < nScore; l++)
        {
            int i = ((l + 1) * nWidth) / 24;
            g.setColor(slimeColours[p1Col]);
            g.fillOval(i, 20, k, k);
            g.setColor(Color.white);
            g.drawOval(i, 20, k, k);
        }

        for(int i1 = 0; i1 < 10 - nScore; i1++)
        {
            int j = nWidth - ((i1 + 1) * nWidth) / 24 - k;
            g.setColor(slimeColours[p2Col]);
            g.fillOval(j, 20, k, k);
            g.setColor(Color.white);
            g.drawOval(j, 20, k, k);
        }

    }

    public void run()
    {
        replayPos = replayStart = 0;
        p1Col = 0;
        p2Col = 1;
        scoringRun = 0;
        fP1Touched = fP2Touched = false;
        nPointsScored = 0;
        startTime = System.currentTimeMillis();
        while(nScore != 0 && nScore != 10 && gameThread != null) 
        {
            gameTime = System.currentTimeMillis() - startTime;
            SaveReplayData();
            p1OldX = p1X;
            p1OldY = p1Y;
            p2OldX = p2X;
            p2OldY = p2Y;
            ballOldX = ballX;
            ballOldY = ballY;
            drawScores();
            MoveSlimers();
            DrawSlimers();
            DrawStatus();
            screen.setColor(ground);
            screen.fillRect(0, (4 * nHeight) / 5, nWidth, nHeight / 5);
            screen.setColor(Color.white);
            screen.fillRect(nWidth / 2 - 2, (7 * nHeight) / 10, 4, nHeight / 10 + 5);
            if (buffered)getGraphics().drawImage(buffer,0,0,null);
            if(ballY < 35)
            {
                long l = System.currentTimeMillis();
                nPointsScored++;
                nScore += ballX <= 500 ? -1 : 1;
                if ((ballX <= 500) && (scoringRun >= 0)) scoringRun++;
                else if ((ballX > 500) && (scoringRun <= 0)) scoringRun--;
                else if ((ballX <= 500) && (scoringRun <= 0)) scoringRun = 1;
                else if ((ballX > 500) && (scoringRun >= 0)) scoringRun = -1;
                promptMsg = ballX <= 500 ? slimeColText[p2Col] : slimeColText[p1Col];
                if(!fP1Touched && !fP2Touched)
                    promptMsg = "What can I say?";
                else
                if ((scoringRun<0?-scoringRun:scoringRun) == scoringRunForSuper)
                    promptMsg += "is on fire!";
                else
                if(ballX > 500 && fP1Touched && !fP2Touched || ballX <= 500 && !fP1Touched && fP2Touched)
                    promptMsg += "aces the serve!";
                else
                if(ballX > 500 && !fP1Touched && fP2Touched || ballX <= 500 && fP1Touched && !fP2Touched)
                    promptMsg += "dies laughing! :P";
                else
                    switch(nScore)
                    {
                    case 0: // '\0'
                    case 10: // '\n'
                        if (nPointsScored == 5)
                            promptMsg += "Wins with a QUICK FIVE!!!";
                        else if (scoringRun == 8)
                            promptMsg += "Wins with a BIG NINE!!!";
                        else
                            promptMsg += "Wins!!!";
                        break;

                    case 4: // '\004'
                        promptMsg += ballX >= 500 ? "Scores!" : "takes the lead!!";
                        break;

                    case 6: // '\006'
                        promptMsg += ballX <= 500 ? "Scores!" : "takes the lead!!";
                        break;

                    case 5: // '\005'
                        promptMsg += "Equalizes!";
                        break;

                    default:
                        promptMsg += "Scores!";
                        break;
                    }
                fCanChangeCol = false;
                boolean flag = nScore != 0 && nScore != 10;
                int i = ballX;
                drawPrompt();
                if (buffered)getGraphics().drawImage(buffer,0,0,null);
                if(flag)
                {
                    drawPrompt("Click mouse for replay...", 1);
                    mousePressed = false;
                    if(gameThread != null)
                        try
                        {
                            Thread.sleep(2500L);
                        }
                        catch(InterruptedException _ex) { }
                    if(mousePressed)
                    {
                        SaveReplayData();
                        DoReplay();
                    }
                } else
                if(gameThread != null)
                    try
                    {
                        Thread.sleep(2500L);
                    }
                    catch(InterruptedException _ex) { }
                promptMsg = "";
                drawPrompt();
                fCanChangeCol = true;
                if(flag)
                {
                    p1X = 200;
                    p1Y = 0;
                    p2X = 800;
                    p2Y = 0;
                    p1XV = 0;
                    p1YV = 0;
                    p2XV = 0;
                    p2YV = 0;
                    ballX = i >= 500 ? 200 : 800;
                    ballY = 400;
                    ballVX = 0;
                    ballVY = 0;
                    replayStart = replayPos = 0;
                    fP1Touched = fP2Touched = false;
                    repaint();
                }
                startTime += System.currentTimeMillis() - l;
            }
            if(gameThread != null)
                try
                {
                    Thread.sleep(20L);
                }
                catch(InterruptedException _ex) { }
        }
        fEndGame = true;
        SaveReplayData();
        DoReplay();
        fInPlay = false;
        promptMsg = "Click the mouse to play...";
        repaint();
    }

    public void init()
    {
        nWidth = size().width;
        nHeight = size().height;
        nScore = 5;
        ballRad = 50;
        fInPlay = fEndGame = false;
        fCanChangeCol = true;
        promptMsg = "Click the mouse to play...";
        buffer = createImage(nWidth, nHeight);
        screen = buffered ? buffer.getGraphics() : getGraphics();
        screen.setFont(new Font(screen.getFont().getName(), 1, 16));
        screen = getGraphics();
        screen.setFont(new Font(screen.getFont().getName(), 1, 16));
    }

    private void DoReplay()
    {
        FontMetrics fontmetrics = screen.getFontMetrics();
        int i = fontmetrics.stringWidth("Replay...");
        int j = fontmetrics.getHeight();
        int k = nWidth / 2 - i / 2;
        int l = nHeight / 2 - j;
        promptMsg = "Click the mouse to continue...";
        mousePressed = false;
        int i1 = replayPos - 1;
        while(!mousePressed) 
        {
            if(++i1 >= 200)
                i1 = 0;
            if(i1 == replayPos)
            {
                try
                {
                    Thread.sleep(1000L);
                }
                catch(InterruptedException _ex) { }
                i1 = replayStart;
                paint(getGraphics());
            }
            ReplayFrame(i1, k, l, i, j, false);
        }
        promptMsg = "";
        paint(getGraphics());
    }

    private void DoFatality()
    {
        // PLEASE, someone put something funny/interesting here :)
    }
}