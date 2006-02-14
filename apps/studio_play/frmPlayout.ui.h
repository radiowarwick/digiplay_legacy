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

	QCustomEvent *config_refresh = new QCustomEvent(30001);
	QApplication::postEvent(this, config_refresh);

	cout << "Creating trigger on configuration settings..." << endl;
	dbTrigger = new triggerThread(this, QString(conf->getDBConnectString()), 1);
	cout << " -> Created trigger thread" << endl;
	dbTrigger->start();
	cout << " -> Trigger active." << endl;

	sys_page = 0;
	stationAudioSet = NULL;
	userAudioSet = NULL;
	AudioWall_Init();
	delete grpUCart;
}

void frmPlayout::destroy() {
	delete conf;
}

// START Events ======================================================
void frmPlayout::customEvent(QCustomEvent *event) {
	switch (event->type()) {
		case 20001:	{
			eventData *e_data = (eventData*)event->data();
			switch (e_data->t) {
				case EVENT_TYPE_STOP: {
					btnPlay1->setPixmap(*pixPlay);
					if (conf->getParam("next_on_showplan") != "") {
			        	btnLoadPlaylist1->setEnabled(true);
					}
					lblCounter1->setPaletteForegroundColor(QColor(QRgb(0)));
					if (lblPlayerTime1->text() == "REMAIN")
					    lblCounter1->setText(getTime(player1->getLength()));
					else
					    lblCounter1->setText(getTime(0));
					sldSeek1->setValue(0);
					sldSeek1->setMaxValue(player1->getLength());
		        	break;
				}
				case EVENT_TYPE_PLAY: {
					break;
				}
				case EVENT_TYPE_SMPL: {
					sldSeek1->setValue(e_data->smpl);
                    if (e_data->smpl != 0 
							&& (player1->getLength()-e_data->smpl)/44100 < 20) {
						lblCounter1->setPaletteForegroundColor(
											QColor(QRgb(16711680)));
					}
					else {
						lblCounter1->setPaletteForegroundColor(
											QColor(QRgb(0)));
					}
					if (lblPlayerTime1->text() == "REMAIN") {
						e_data->smpl = player1->getLength() - e_data->smpl;
					}
					lblCounter1->setText(getTime(e_data->smpl));
					break;
				}
				case EVENT_TYPE_MAX_SMPL: {
					sldSeek1->setMaxValue(e_data->smpl);
					break;
				}
				case EVENT_TYPE_END: {
					break;
				}
			}
			break;
		}
		case 20002: {
            eventData *e_data = (eventData*)event->data();
            switch (e_data->t) {
                case EVENT_TYPE_STOP: {
                    btnPlay2->setPixmap(*pixPlay);
					if (conf->getParam("next_on_showplan") != "") {
	                    btnLoadPlaylist2->setEnabled(true);
					}
                    lblCounter2->setPaletteForegroundColor(QColor(QRgb(0)));
					if (lblPlayerTime2->text() == "REMAIN")
					    lblCounter2->setText(getTime(player2->getLength()));
					else
					    lblCounter2->setText(getTime(0));
					sldSeek2->setValue(0);
					sldSeek2->setMaxValue(player2->getLength());
                    break;
                }
                case EVENT_TYPE_PLAY: {
                    break;
                }
                case EVENT_TYPE_SMPL: {
					sldSeek2->setValue(e_data->smpl);
                    if (e_data->smpl != 0 
							&& (player2->getLength()-e_data->smpl)/44100 < 20) {
                        lblCounter2->setPaletteForegroundColor(
                                            QColor(QRgb(16711680)));
                    }
                    else {
                        lblCounter2->setPaletteForegroundColor(
                                            QColor(QRgb(0)));
                    }
					if (lblPlayerTime2->text() == "REMAIN") {
						e_data->smpl = player2->getLength() - e_data->smpl;
					}
					lblCounter2->setText(getTime(e_data->smpl));
                    break;
                }
                case EVENT_TYPE_MAX_SMPL: {
					sldSeek2->setMaxValue(e_data->smpl);
                    break;
                }
                case EVENT_TYPE_END: {
                    break;
                }
            }
			break;
		}
		case 20003: {
            eventData *e_data = (eventData*)event->data();
            switch (e_data->t) {
                case EVENT_TYPE_STOP: {
                    btnPlay3->setPixmap(*pixPlay);
					if (conf->getParam("next_on_showplan") != "") {
	                    btnLoadPlaylist3->setEnabled(true);
					}
                    lblCounter3->setPaletteForegroundColor(QColor(QRgb(0)));
					if (lblPlayerTime3->text() == "REMAIN")
					    lblCounter3->setText(getTime(player3->getLength()));
					else
					    lblCounter3->setText(getTime(0));
					sldSeek3->setValue(0);
					sldSeek3->setMaxValue(player3->getLength());
                    break;
                }
                case EVENT_TYPE_PLAY: {
                    break;
                }
                case EVENT_TYPE_SMPL: {
					sldSeek3->setValue(e_data->smpl);
                    if (e_data->smpl != 0 
							&& (player3->getLength()-e_data->smpl)/44100 < 20) {
                        lblCounter3->setPaletteForegroundColor(
                                            QColor(QRgb(16711680)));
                    }
                    else {
                        lblCounter3->setPaletteForegroundColor(
                                            QColor(QRgb(0)));
                    }
					if (lblPlayerTime3->text() == "REMAIN") {
						e_data->smpl = player3->getLength() - e_data->smpl;
					}
					lblCounter3->setText(getTime(e_data->smpl));
                    break;
                }
                case EVENT_TYPE_MAX_SMPL: {
					sldSeek3->setMaxValue(e_data->smpl);
                    break;
                }
                case EVENT_TYPE_END: {
                    break;
                }
            }
			break;
		}							  
		case 20004: {
			eventData *e_data = (eventData*)event->data();
			if (e_data->index < 0) break;
			switch (e_data->t) {
			case EVENT_TYPE_STOP: {
					if (sys_page == sys_active_page) {
						int clip_id = e_data->index % 12;
						audioClip A = stationAudioSet->at(sys_page)->clip[clip_id];
						A.btn->setText(A.text);
						A.btn->setPaletteForegroundColor(QColor(QRgb(A.fg)));
						A.btn->setPaletteBackgroundColor(QColor(QRgb(A.bg)));
					}
					sys_active_page = sys_page;
					lblSCartCounter->setText("");
					break;
				}
			case EVENT_TYPE_PLAY: {
					int clip_id = e_data->index % 12;
					audioClip A = stationAudioSet->at(sys_page)->clip[clip_id];
					A.btn->setPaletteForegroundColor(QColor(QRgb(16776960))); //yellow
					A.btn->setPaletteBackgroundColor(QColor(QRgb(16711680))); //red
					sys_active_page = sys_page;
					lblSCartCounter->setText("");
					break;
				}
			case EVENT_TYPE_SMPL: {
					if (audiowall->get_state() == 1 && sys_page == sys_active_page) {
						int clip_id = e_data->index - 12*sys_page;
						audioClip A = stationAudioSet->at(sys_page)->clip[clip_id];
						A.btn->setText("PLAYING\n" + getTime(e_data->smpl));
					}
					lblSCartCounter->setText(getTime(e_data->smpl));
					break;
				}
			case EVENT_TYPE_MAX_SMPL: {
					break;
				}
			case EVENT_TYPE_END: {
					break;
				}
			}
		break;				
		}
	case 30001: {
			conf->requery();
			if (conf->getParam("next_on_showplan") == "") {
				btnLoadPlaylist1->setEnabled(false);
				btnLoadPlaylist2->setEnabled(false);
				btnLoadPlaylist3->setEnabled(false);
			}
			else {
				if (player1->getState() != STATE_PLAY)
				btnLoadPlaylist1->setEnabled(true);
				if (player2->getState() != STATE_PLAY)
				btnLoadPlaylist2->setEnabled(true);
				if (player3->getState() != STATE_PLAY)
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
	Transaction T(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T.exec(SQL);
	T.abort();

	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player1->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle1->setText(R[0]["title"].c_str());
	lblArtist1->setText(R[0]["artist"].c_str());
	btnPlay1->setEnabled(true);
	btnStop1->setEnabled(true);
	//btnSeekBack1->setEnabled(true);
	//btnSeekForward1->setEnabled(true);
	sldSeek1->setEnabled(true);
}   

void frmPlayout::Player1_Play() {
	switch (player1->getState()) {
	case STATE_STOP:
		player1->do_play();
		btnPlay1->setPixmap(*pixPause);
		btnLoadPlaylist1->setEnabled(false);
		break;
	case STATE_PLAY:
		player1->do_pause();
		btnPlay1->setPixmap(*pixPlay);
		if (conf->getParam("next_on_showplan") != "") {
			btnLoadPlaylist1->setEnabled(true);
		}
		break;
	case STATE_PAUSE:
		player1->do_resume();
		btnPlay1->setPixmap(*pixPause);
		btnLoadPlaylist1->setEnabled(false);
		break;
	}
}

void frmPlayout::Player1_Stop() {
	player1->do_stop();
	btnPlay1->setEnabled(true);
	if (conf->getParam("next_on_showplan") != "") {
		btnLoadPlaylist1->setEnabled(true);
	}
}


void frmPlayout::Player1_Seek() {
	player1->do_seek(sldSeek1->value());
}

void frmPlayout::Player2_Load() {
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction T(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T.exec(SQL);
	T.abort();
	
	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player2->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle2->setText(R[0]["title"].c_str());
	lblArtist2->setText(R[0]["artist"].c_str());
	btnPlay2->setEnabled(true);
	btnStop2->setEnabled(true);
	//btnSeekBack2->setEnabled(true);
	//btnSeekForward2->setEnabled(true);
	sldSeek2->setEnabled(true);
}   

void frmPlayout::Player2_Play() {

	switch (player2->getState()) {
	case STATE_STOP:
		player2->do_play();
		btnPlay2->setPixmap(*pixPause);
		btnLoadPlaylist2->setEnabled(false);
		break;
	case STATE_PLAY:
		player2->do_pause();
		btnPlay2->setPixmap(*pixPlay);
		if (conf->getParam("next_on_showplan") != "") {
			btnLoadPlaylist2->setEnabled(true);
		}
		break;
	case STATE_PAUSE:
		player2->do_resume();
		btnPlay2->setPixmap(*pixPause);
		btnLoadPlaylist2->setEnabled(false);
		break;
	}
}

void frmPlayout::Player2_Stop() {
	player2->do_stop();
	btnPlay2->setEnabled(true);
	if (conf->getParam("next_on_showplan") != "") {
		btnLoadPlaylist2->setEnabled(true);
	}
}


void frmPlayout::Player2_Seek() {
	player2->do_seek(sldSeek2->value());
}

void frmPlayout::Player3_Load() {
	if (conf->getParam("next_on_showplan") == "") {
		return;
	}
	Transaction T(*C,"");
	string SQL = "SELECT audio.md5 AS md5, audio.title AS title, artists.name as artist, "
				 "audio.intro_smpl as start, audio.extro_smpl as end, "
				 "archives.localpath AS path "
				 "FROM audio,artists,audioartists,archives "
				 "WHERE audio.archive=archives.id AND audioartists.audio=audio.id "
				 "AND audioartists.artist = artists.id AND audio.md5='" 
				 + conf->getParam("next_on_showplan") + "'";
	Result R = T.exec(SQL);
	T.abort();

	string f = R[0]["path"].c_str() + string("/") + (string(R[0]["md5"].c_str())).substr(0,1)
			   + string("/") + R[0]["md5"].c_str();
	player3->do_load(new QString(f), atoi(R[0]["start"].c_str()),atoi(R[0]["end"].c_str()));
	conf->setParam("next_on_showplan","");
	lblTitle3->setText(R[0]["title"].c_str());
	lblArtist3->setText(R[0]["artist"].c_str());
	btnPlay3->setEnabled(true);
	btnStop3->setEnabled(true);
	//btnSeekBack3->setEnabled(true);
	//btnSeekForward3->setEnabled(true);
	sldSeek3->setEnabled(true);
}   

void frmPlayout::Player3_Play() {
	switch (player3->getState()) {
	case STATE_STOP:
		player3->do_play();
		btnPlay3->setPixmap(*pixPause);
		btnLoadPlaylist3->setEnabled(false);
		break;
	case STATE_PLAY:
		player3->do_pause();
		btnPlay3->setPixmap(*pixPlay);
		if (conf->getParam("next_on_showplan") != "") {
			btnLoadPlaylist3->setEnabled(true);
		}
		break;
	case STATE_PAUSE:
		player3->do_resume();
		btnPlay3->setPixmap(*pixPause);
		btnLoadPlaylist3->setEnabled(false);
		break;
	}
}

void frmPlayout::Player3_Stop() {
	player3->do_stop();
	btnPlay3->setEnabled(true);
	if (conf->getParam("next_on_showplan") != "") {
		btnLoadPlaylist3->setEnabled(true);
	}
}

void frmPlayout::Player3_Seek() {
    player3->do_seek(sldSeek3->value());
}

void frmPlayout::Player1_Time() {
    if (lblPlayerTime1->text() == "REMAIN") {
        lblPlayerTime1->setText("ELAPSED");
    }
    else {
        lblPlayerTime1->setText("REMAIN");
    }	
	player1->do_updateCounter();
}


void frmPlayout::Player2_Time(){
    if (lblPlayerTime2->text() == "REMAIN") {
        lblPlayerTime2->setText("ELAPSED");
    }
    else {
        lblPlayerTime2->setText("REMAIN");
    }	
	player2->do_updateCounter();
}


void frmPlayout::Player3_Time() {
    if (lblPlayerTime3->text() == "REMAIN") {
        lblPlayerTime3->setText("ELAPSED");
    }
    else {
        lblPlayerTime3->setText("REMAIN");
    }
	player3->do_updateCounter();
}

void frmPlayout::AudioWall_Init() {
	QPushButton *btnCurrent;
	
	Transaction T(*C,"");
	sys_page_count = atoi(T.exec("SELECT max(cartwalls.page) "
							 "FROM cartwalls,cartsets "
							 "WHERE cartwalls.cartset = 0")[0][0].c_str()) + 1;
	usr_page_count = atoi(T.exec("SELECT max(cartwalls.page) "
							 "FROM cartwalls,cartsets "
							 "WHERE cartwalls.cartset = 1")[0][0].c_str()) + 1;
	T.abort();
	
	// Configure Station Audio Wall
	// Set of all audio walls (pages)
	if (stationAudioSet) {
		for (unsigned int i = 0; i < stationAudioSet->size(); i++) 
			delete stationAudioSet->at(i);
		delete stationAudioSet;
	}
	stationAudioSet = new vector<audioWall*>;

	// Create enough pages on the system audio wall
	for (int i = 0; i < sys_page_count; i++) {
		stationAudioSet->push_back(new audioWall);
	}
	
	// Create the buttons
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			btnCurrent = new QPushButton( grpSCart, QString::number(i*3+j));
			btnCurrent->setGeometry(j*150 + 10, i*70 + 20, 140, 60);
			QFont f = btnCurrent->font();
			f.setPointSize(14);
			btnCurrent->setFont(f);
			btnCurrent->setEnabled(false);
			for (int page = 0; page < sys_page_count; page++)
				stationAudioSet->at(page)->clip[i*3+j].btn = btnCurrent;
			connect(btnCurrent,SIGNAL(pressed()),this,SLOT(AudioWall_Play()));
		}
	}
	
	// Configure User Audio Wall
	if (userAudioSet) {
		for (unsigned int i = 0; i < userAudioSet->size(); i++) 
			delete userAudioSet->at(i);
		delete userAudioSet;
	}
	userAudioSet = new vector<audioWall*>;
	
	// Create enough pages for user audio wall
	for (int i = 0; i < usr_page_count; i++) {
		userAudioSet->push_back(new audioWall);
	}
	
	// Create the buttons
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			btnCurrent = new QPushButton( grpUCart, QString::number(i*3+j));
			btnCurrent->setGeometry(j*150 + 10, i*70 + 20, 140, 60);
			btnCurrent->setEnabled(false);
			for (int page = 0; page < usr_page_count; page++)
				userAudioSet->at(page)->clip[i*3+j].btn = btnCurrent;
		}
	}
	
	// Load all the cart information into structures
	AudioWall_Load();
	
	// Load the audio into channels
	sys_active_page = 0;
	for (int page = 0; page < sys_page_count; page++) {
		for (int i = 0; i < 12; i++) {
			audioClip A = stationAudioSet->at(page)->clip[i];
			audiowall->do_load(new QString(A.fn),A.start,A.end);
		}
	}
	
	// Display text and colours on buttons etc
	AudioWall_Display();
}


void frmPlayout::AudioWall_Play() {
	QPushButton *sender = (QPushButton*)QObject::sender();
	short x = atoi(sender->name());
	if (audiowall->get_active_channel() == 12*sys_page+x)
		audiowall->do_stop(12*sys_page+x);
	else {
		audiowall->do_play(12*sys_page+x);
		//if (audiowall->get_active_channel() > 0) 
			//sys_active_page = sys_page;		
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
	T.abort();
	
	unsigned int i = 0;
	string path = "", md5 = "";
	short cart = 0, page = 0, test = 0, p = 0;
	QColor fg, bg;
	
	// Process each cart
	vector<audioWall*> *currentSet;
	while (i < R.size()) {
		if (atoi(R[i]["userid"].c_str()) == 0) currentSet = stationAudioSet;
		else currentSet = userAudioSet;
		path = R[i]["path"].c_str();
		md5 = R[i]["md5"].c_str();
		path += "/" + md5.substr(0,1) + "/" + md5;
		cart = atoi(R[i]["cart"].c_str());
		page = atoi(R[i]["page"].c_str());
		cout << i << " Page: " << page << "   Cart: " << cart << endl;
		if (cart > 11) cout << "ERROR: More than 12 carts. DB Integrity failed." << endl;
		currentSet->at(page)->clip[cart].fn = path;
		currentSet->at(page)->clip[cart].start = atoi(R[i]["start"].c_str());
		currentSet->at(page)->clip[cart].end = atoi(R[i]["end"].c_str());
		currentSet->at(page)->clip[cart].text = R[i]["text"].c_str();
		currentSet->at(page)->name = R[i]["cartset"].c_str();
		currentSet->at(page)->description = R[i]["desc"].c_str();
		
		test = 12*page+cart;
		// Process each property for current cart
		while (i<R.size() && test==12*atoi(R[i]["page"].c_str())+atoi(R[i]["cart"].c_str())) {
			p = atoi(R[i]["property"].c_str());
			switch (p) {
			case 0:
				currentSet->at(page)->clip[cart].fg = atoi(R[i]["prop_value"].c_str());
				break;
			case 1:
				currentSet->at(page)->clip[cart].bg = atoi(R[i]["prop_value"].c_str());
				break;
			}
			i++;
		}
	}
}

// Display's the carts for a page specified by sys_page
void frmPlayout::AudioWall_Display() {
	audioWall *currentPage = stationAudioSet->at(sys_page);
	grpSCart->setTitle(currentPage->description);
	for (int i = 0; i < 12; i++) {
		audioClip A = currentPage->clip[i];
		if (A.fn != "") {
			A.btn->setText(A.text);
			A.btn->setPaletteForegroundColor(QColor(QRgb(A.fg)));
			A.btn->setPaletteBackgroundColor(QColor(QRgb(A.bg)));
			A.btn->setEnabled(true);
		}
		else {
			A.btn->setText("");
			A.btn->setPaletteForegroundColor(QColor(QRgb(0)));
			A.btn->setPaletteBackgroundColor(QColor(QRgb(12632256)));
			A.btn->setEnabled(false);
		}
	}
	lblSCartPage->setText("Page " + QString::number(sys_page+1) + "/" 
						  + QString::number(sys_page_count));
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


void frmPlayout::AudioWallPageNext() {
	if (sys_page < sys_page_count - 1) {
		sys_page++;
		AudioWall_Display();
	}
}


void frmPlayout::AudioWallPagePrev() {
	if (sys_page > 0) {
		sys_page--;
		AudioWall_Display();
	}
}
