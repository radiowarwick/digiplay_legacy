/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
void frmPlayout::init() {
	path = qApp->applicationDirPath();
	pixPlay = new QPixmap(path + "/images/play.png");
	pixPause = new QPixmap(path + "/images/pause.png");
	pixStop = new QPixmap(path + "/images/stop.png");
	pixSeekback = new QPixmap(path + "/images/fastbackward.png");
	pixSeekforward = new QPixmap(path + "/images/fastforward.png");
	pixReset = new QPixmap(path + "/images/reset.png");
	cout << path << endl;
	// Set up button images
	btnPlay1->setPixmap(*pixPlay);
	btnPlay2->setPixmap(*pixPlay);
	btnPlay3->setPixmap(*pixPlay);
	btnStop1->setPixmap(*pixStop);
	btnStop2->setPixmap(*pixStop);
	btnStop3->setPixmap(*pixStop);
	btnSeekBack1->setPixmap(*pixSeekback);
	btnSeekBack2->setPixmap(*pixSeekback);
	btnSeekBack3->setPixmap(*pixSeekback);
	btnSeekForward1->setPixmap(*pixSeekforward);
	btnSeekForward2->setPixmap(*pixSeekforward);
	btnSeekForward3->setPixmap(*pixSeekforward);
	btnReset1->setPixmap(*pixReset);
	btnReset2->setPixmap(*pixReset);
	btnReset3->setPixmap(*pixReset);
	btnSCartPrev->setPixmap(*pixSeekback);
	btnSCartNext->setPixmap(*pixSeekforward);
	btnUCartPrev->setPixmap(*pixSeekback);
	btnUCartNext->setPixmap(*pixSeekforward);
	
	cout << "Connecting to database..." << endl;
	conf = new config("digiplay");
    QCustomEvent *config_refresh = new QCustomEvent(30000);
    QApplication::postEvent(this, config_refresh);
	C = new Connection(conf->getDBConnectString());
	cout << " -> Connected." << endl;
	
	cout << "Initialising Digital Playout Hardware..." << endl;
	player1 = new playerThread(this, 1);
	player2 = new playerThread(this, 2);	
	player3 = new playerThread(this, 3);
	audiowall = new audiowallthread(this, 4);
	player1->start();
	usleep(100000);
	player2->start();
	usleep(100000);
	player3->start();
	usleep(100000);
	audiowall->start();
	usleep(500000);
	cout << " -> Hardware initialisation complete." << endl;
	
	cout << "Creating trigger on configuration settings..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1, 5);
	cout << " -> Created trigger thread" << endl;
	dbTrigger->start();
	cout << " -> Trigger active." << endl;
	AudioWall_Init();
}

void frmPlayout::destroy() {
	delete conf;
}

// START Events ======================================================
void frmPlayout::customEvent(QCustomEvent *event) {
	//cout << "Event received: " << event->type() << endl;
	switch (event->type()) {
	case 20001: {
			eventData *e_data = (eventData*)event->data();
			if (e_data->index < 0) break;
			switch (e_data->t) {
			case EVENT_TYPE_STOP: {
					audioClip A = stationWall->at(0)->clip[e_data->index];
					A.btn->setText(A.text);
					A.btn->setPaletteForegroundColor(QColor(QRgb(A.fg)));
					A.btn->setPaletteBackgroundColor(QColor(QRgb(A.bg)));
					break;
				}
			case EVENT_TYPE_PLAY: {
					break;
				}
			case EVENT_TYPE_SMPL: {
					if (audiowall->get_state() == 1) {
						audioClip A = stationWall->at(0)->clip[e_data->index];
						A.btn->setText("PLAYING\n" + getTime(e_data->smpl));
					}
					break;
				}
			case EVENT_TYPE_MAX_SMPL: {
					break;
				}
			}
		break;				
		}
	case 20010: {       // Player1 Counter Update
			QString *s = (QString *) event->data();
			lblCounter1->setText(*s);
			break;
		}
	case 20011: {       // Player1 Slider Update
			int *s  = (int *) event->data();
			sldSeek1->setValue(*s);
			break;
		}
	case 20012: {       // Player1 Slider MaxValue Update
			int *s = (int *) event->data();
			sldSeek1->setMaxValue(*s);
			break;
		}
	case 20013: {       // Player1 Stop Event
			btnPlay1->setPixmap(*pixPlay);
			break;
		}
	case 20020: {       // Player2 Counter Update
			QString *s = (QString *) event->data();
			lblCounter2->setText(*s);
			break;
		}
	case 20021: {       // Player2 Slider Update
			int *s  = (int *) event->data();
			sldSeek2->setValue(*s);
			break;
		}
	case 20022: {       // Player2 Slider MaxValue Update
			int *s = (int *) event->data();
			sldSeek2->setMaxValue(*s);
			break;
		}
	case 20023: {       // Player2 Stop Event
			btnPlay2->setPixmap(*pixPlay);
			break;
		}
	case 20030: {       // Player3 Counter Update
			QString *s = (QString *) event->data();
			lblCounter3->setText(*s);
			break;
		}
	case 20031: {       // Player3 Slider Update
			int *s  = (int *) event->data();
			sldSeek3->setValue(*s);
			break;
		}
	case 20032: {       // Player3 Slider MaxValue Update
			int *s = (int *) event->data();
			sldSeek3->setMaxValue(*s);
			break;
		}
	case 20033: {       // Player2 Stop Event
			btnPlay3->setPixmap(*pixPlay);
			break;
		}
	case 30000: {
			conf->requery();
			if (conf->getParam("next_on_showplan") == "") {
				btnLoadPlaylist1->setEnabled(false);
				btnLoadPlaylist2->setEnabled(false);
				btnLoadPlaylist3->setEnabled(false);
			}
			else {
				btnLoadPlaylist1->setEnabled(true);
				btnLoadPlaylist2->setEnabled(true);
				btnLoadPlaylist3->setEnabled(true);
			}
			break;
		}
	default: {
			qWarning("Unknown event type: %d", event->type());
			break;
		}
	}
}

void frmPlayout::Player1_Load() {
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	pqxx::Transaction *T = new pqxx::Transaction(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T->exec(SQL);
	T->abort();
	delete T;
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player1->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle1->setText(R[0]["title"].c_str());
	lblArtist1->setText(R[0]["artist"].c_str());
	btnPlay1->setEnabled(true);
	btnStop1->setEnabled(true);
	btnSeekBack1->setEnabled(true);
	btnSeekForward1->setEnabled(true);
	sldSeek1->setEnabled(true);
}   

void frmPlayout::Player1_Play() {
	cout << "State: " << player1->getState() << endl;
	switch (player1->getState()) {
	case STATE_STOP:
		player1->do_play();
		btnPlay1->setPixmap(*pixPause);
		break;
	case STATE_PLAY:
		player1->do_pause();
		btnPlay1->setPixmap(*pixPlay);
		break;
	case STATE_PAUSE:
		player1->do_resume();
		btnPlay1->setPixmap(*pixPause);
		break;
	}
}

void frmPlayout::Player1_Stop() {
	player1->do_stop();
	btnPlay1->setEnabled(true);
}

void frmPlayout::Player2_Load() {
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction *T = new Transaction(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T->exec(SQL);
	T->abort();
	delete T;
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player2->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle2->setText(R[0]["title"].c_str());
	lblArtist2->setText(R[0]["artist"].c_str());
	btnPlay2->setEnabled(true);
	btnStop2->setEnabled(true);
	btnSeekBack2->setEnabled(true);
	btnSeekForward2->setEnabled(true);
	sldSeek2->setEnabled(true);
}   

void frmPlayout::Player2_Play() {

	switch (player2->getState()) {
	case STATE_STOP:
		player2->do_play();
		btnPlay2->setPixmap(*pixPause);
		break;
	case STATE_PLAY:
		player2->do_pause();
		btnPlay2->setPixmap(*pixPlay);
		break;
	case STATE_PAUSE:
		player2->do_resume();
		btnPlay2->setPixmap(*pixPause);
		break;
	}
}

void frmPlayout::Player2_Stop() {
	player2->do_stop();
	btnPlay2->setEnabled(true);
}

void frmPlayout::Player3_Load() {
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction *T = new Transaction(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T->exec(SQL);
	T->abort();
	delete T;
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player3->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle3->setText(R[0]["title"].c_str());
	lblArtist3->setText(R[0]["artist"].c_str());
	btnPlay3->setEnabled(true);
	btnStop3->setEnabled(true);
	btnSeekBack3->setEnabled(true);
	btnSeekForward3->setEnabled(true);
	sldSeek3->setEnabled(true);
}   

void frmPlayout::Player3_Play() {

	switch (player3->getState()) {
	case STATE_STOP:
		player3->do_play();
		btnPlay3->setPixmap(*pixPause);
		break;
	case STATE_PLAY:
		player3->do_pause();
		btnPlay3->setPixmap(*pixPlay);
		break;
	case STATE_PAUSE:
		player3->do_resume();
		btnPlay3->setPixmap(*pixPause);
		break;
	}
}

void frmPlayout::Player3_Stop() {
	player3->do_stop();
	btnPlay3->setEnabled(true);
}



void frmPlayout::Player1_Time() {
    if (lblPlayerTime1->text() == "REMAIN") {
        lblPlayerTime1->setText("ELAPSED");
        player1->setTimeMode(TIME_MODE_ELAPSED);
    }
    else {
        lblPlayerTime1->setText("REMAIN");
        player1->setTimeMode(TIME_MODE_REMAIN);
    }	
}


void frmPlayout::Player2_Time(){
    if (lblPlayerTime2->text() == "REMAIN") {
        lblPlayerTime2->setText("ELAPSED");
        player2->setTimeMode(TIME_MODE_ELAPSED);
    }
    else {
        lblPlayerTime2->setText("REMAIN");
        player2->setTimeMode(TIME_MODE_REMAIN);
    }	
}


void frmPlayout::Player3_Time() {
    if (lblPlayerTime3->text() == "REMAIN") {
        lblPlayerTime3->setText("ELAPSED");
        player3->setTimeMode(TIME_MODE_ELAPSED);
    }
    else {
        lblPlayerTime3->setText("REMAIN");
        player3->setTimeMode(TIME_MODE_REMAIN);
    }	
}


void frmPlayout::AudioWall_Init() {
	QPushButton *btnCurrent;	
	
	// Configure Station Audio Wall
	stationWall = new vector<audioWall*>;
	audioWall *stn1 = new audioWall;
	stationWall->push_back(stn1);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			btnCurrent = new QPushButton( grpSCart, QString::number(i*3+j));
			btnCurrent->setGeometry(j*150 + 10, i*70 + 20, 140, 60);
			btnCurrent->setEnabled(false);
			stationWall->at(0)->clip[i*3+j].btn = btnCurrent;
			connect(btnCurrent,SIGNAL(clicked()),this,SLOT(AudioWall_Play()));
		}
	}
	
	// Configure User Audio Wall
	userWall = new vector<audioWall*>;
	audioWall *usr1 = new audioWall;
	userWall->push_back(usr1);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			btnCurrent = new QPushButton( grpUCart, QString::number(i*3+j));
			btnCurrent->setGeometry(j*150 + 10, i*70 + 20, 140, 60);
			btnCurrent->setEnabled(false);
			userWall->at(0)->clip[i*3+j].btn = btnCurrent;
		}
	}
	AudioWall_Load();
	AudioWall_Display();
}


void frmPlayout::AudioWall_Play() {
	QPushButton *sender = (QPushButton*)QObject::sender();
	short x = atoi(sender->name());
	if (audiowall->get_active_channel() == x)
		audiowall->do_stop(x);
	else if (audiowall->get_active_channel() < 0) {
		audioClip A = stationWall->at(0)->clip[x];
		A.btn->setPaletteForegroundColor(QColor(QRgb(16776960)));
		A.btn->setPaletteBackgroundColor(QColor(QRgb(16711680)));
		audiowall->do_play(x);
	}
}


void frmPlayout::AudioWall_Load() {
	Transaction T(*C,"");
	Result R = T.exec("SELECT audio.md5 AS md5, audio.start_smpl AS start, "
					  "audio.end_smpl AS end, cartsaudio.cart AS cart, "
					  "cartsaudio.text AS text, cartwalls.name AS name, "
					  "cartwalls.description AS desc, cartsets.name AS cartset, "
					  "cartwalls.page AS page, "
					  "cartsets.description AS cartset_desc, cartsets.userid AS userid, "
					  "cartsets.directory AS dir, cartproperties.id AS property, "
					  "cartstyleprops.value AS prop_value, archives.localpath AS path "
					  "FROM audio, cartsaudio, cartwalls, cartsets, cartstyle, "
					  "cartstyleprops, cartproperties, archives "
					  "WHERE cartsaudio.audio = audio.id "
					  "AND cartsaudio.cartwall = cartwalls.id "
					  "AND cartwalls.cartset = cartsets.id "
					  "AND cartsaudio.style = cartstyle.id "
					  "AND cartstyleprops.style = cartstyle.id "
					  "AND cartstyleprops.property = cartproperties.id "
					  "AND audio.archive = archives.id "
					  "AND cartsets.userid=0 "
					  "ORDER BY cartwalls.id, cartsaudio.cart, cartproperties.id;");
	int i = 0;
	string path = "", md5 = "";
	short cart = 0, page = 0;
	QColor fg, bg;

	// Process each cart
	vector<audioWall*> *currentWall;
	while (i < R.size()) {
		if (atoi(R[i]["userid"].c_str()) == 0) currentWall = stationWall;
		else currentWall = userWall;
		path = R[i]["path"].c_str();
		md5 = R[i]["md5"].c_str();
		path += "/" + md5.substr(0,1) + "/" + md5;
		cart = atoi(R[i]["cart"].c_str());
		page = atoi(R[i]["page"].c_str());
		
		if (cart > 11) cout << "ERROR: More than 12 carts. DB Integrity failed." << endl;
		currentWall->at(page)->clip[cart].fn = path;
		currentWall->at(page)->clip[cart].start = atoi(R[i]["start"].c_str());
		currentWall->at(page)->clip[cart].end = atoi(R[i]["end"].c_str());
		currentWall->at(page)->clip[cart].text = R[i]["text"].c_str();
		currentWall->at(page)->name = R[i]["cartset"].c_str();
		currentWall->at(page)->description = R[i]["cartset_desc"].c_str();
		
		// Process each property for current cart
		while (i < R.size() && md5 == R[i]["md5"].c_str()) {		
			if (atoi(R[i]["property"].c_str()) == 0)
				currentWall->at(page)->clip[cart].fg = atoi(R[i]["prop_value"].c_str());
			if (atoi(R[i]["property"].c_str()) == 1)
				currentWall->at(page)->clip[cart].bg = atoi(R[i]["prop_value"].c_str());
			i++;
		}
	}
}


void frmPlayout::AudioWall_Display() {
	int page = 0;
	audioWall *currentPage = stationWall->at(page);
	grpSCart->setTitle(currentPage->description);
	for (int i = 0; i < 12; i++) {
		audioClip A = currentPage->clip[i];
		if (A.fn != "") {
			A.btn->setText(A.text);
			A.btn->setPaletteForegroundColor(QColor(QRgb(A.fg)));
			A.btn->setPaletteBackgroundColor(QColor(QRgb(A.bg)));
			A.btn->setEnabled(true);
		}
		audiowall->do_load(new QString(A.fn),A.start,A.end);
	}
}


QString frmPlayout::getTime( long smpl ) {
	QString S;
	int mil, sec, min;
	
	mil = smpl/441;
    sec = (int)(mil / 100);
    mil = mil%100;
    min = (int)(sec / 60);
    sec = sec%60;
	if (min < 10) S += "0";
	S += QString::number(min) + ":";
	if (sec < 10) S += "0";
	S += QString::number(sec) + ".";
    if (mil < 10) S += "0";
	S += QString::number(mil);
	return S;
}
