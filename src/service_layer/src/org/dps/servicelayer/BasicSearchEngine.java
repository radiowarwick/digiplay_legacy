package org.dps.servicelayer;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.SessionFactoryUtils;

public class BasicSearchEngine implements ISearchEngine {

	private final static Logger LOGGER = LoggerFactory.getLogger(BasicSearchEngine.class);
	
	private SessionFactory _sessionFactory;
	
	@SuppressWarnings("unchecked")
	public <T> List<T> search(Map<String, String> args_, Class<T> clazz_) {
		Session session = getSession();
		if(args_.containsKey(AUDIO_TITLE) && args_.containsKey(ARTIST_NAME)) {
			LOGGER.info("Searching for: ", args_.get(AUDIO_TITLE), args_.get(ARTIST_NAME));
			Query query = session.createQuery("from Audio where title=? and artist.name=?");
			query.setString(0, args_.get(AUDIO_TITLE));
			query.setString(0, args_.get(ARTIST_NAME));
		
		
			return (List<T>) query.list();
		}
		
		if(args_.containsKey(AUDIO_TITLE)) {
			LOGGER.info("Searching for: ", args_.get(AUDIO_TITLE));
			Query query = session.createQuery("from Audio where title=?");
			query.setString(0, args_.get(AUDIO_TITLE));
		
		
			return (List<T>) query.list();
		}
		return new LinkedList<T>();
	}

	private Session getSession() {
		return SessionFactoryUtils.getSession(_sessionFactory, false);
	}
	
	public void setSessionFactory(SessionFactory sessionFactory_) {
		_sessionFactory = sessionFactory_;
	}

}
