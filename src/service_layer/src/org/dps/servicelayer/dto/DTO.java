package org.dps.servicelayer.dto;

import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.SessionFactoryUtils;

public class DTO implements IDTO {

	private final static Logger LOGGER = LoggerFactory.getLogger(DTO.class);
	
	SessionFactory _sessionFactory;
	
	public Audio getAudio(Long fileID_) {
		Session session = getSession();
		Query query = session.createQuery("from Audio where fileID=?");
		query.setLong(0, fileID_);
		
		LOGGER.info("Searching for: ", fileID_);
		
		 return (Audio) query.uniqueResult();
	}
	
	private Session getSession() {
		return SessionFactoryUtils.getSession(_sessionFactory, false);
	}
	
	public void setSessionFactory(SessionFactory sessionFactory_) {
		_sessionFactory = sessionFactory_;
	}

}
