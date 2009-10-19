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
		
		LOGGER.info("Searching for Audio: {}", fileID_);
		
		 return (Audio) query.uniqueResult();
	}
	
	public Artist getArtist(String name_) {
		Session session = getSession();
		Query query = session.createQuery("from Artist where name=?");
		query.setString(0, name_);
		
		LOGGER.info("Searching for Artist: {}", name_);
		
		 return (Artist) query.uniqueResult();
	}
	
	public Artist getArtist(Long artistID_) {
		Session session = getSession();
		Query query = session.createQuery("from Artist where artistID=?");
		query.setLong(0, artistID_);
		
		LOGGER.info("Searching for Artist: {}", artistID_);
		
		 return (Artist) query.uniqueResult();
	}
	
	@Override
	public Album getAlbum(String name_) {
		Session session = getSession();
		Query query = session.createQuery("from Album where name=?");
		query.setString(0, name_);
		
		LOGGER.info("Searching for Artist: {}", name_);
		
		 return (Album) query.uniqueResult();
	}

	@Override
	public Album getAlbum(Long albumID_) {
		Session session = getSession();
		Query query = session.createQuery("from Album where albumID=?");
		query.setLong(0, albumID_);
		
		LOGGER.info("Searching for Artist: {}", albumID_);
		
		 return (Album) query.uniqueResult();
	}
	
	@Override
	public File getFile(Long fileID_) {
		Session session = getSession();
		Query query = session.createQuery("from File where fileID=?");
		query.setLong(0, fileID_);
		
		LOGGER.info("Searching for File: {}", fileID_);
		
		return (File) query.uniqueResult();
	}
	
	public <T> T saveOrUpdate(T item_) {
		Session session = getSession();
		session.saveOrUpdate(item_);
		//FIXME: why does it need this!!
		session.flush();
		return item_;
	}
	
	public <T> T delete(T item_) {
		Session session = getSession();
		session.delete(item_);
		//TODO: Do we need this?
		session.flush();
		return item_;
	}
	
	private Session getSession() {
		return SessionFactoryUtils.getSession(_sessionFactory, false);
	}
	
	public void setSessionFactory(SessionFactory sessionFactory_) {
		_sessionFactory = sessionFactory_;
	}

}
