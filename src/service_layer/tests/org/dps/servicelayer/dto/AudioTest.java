package org.dps.servicelayer.dto;

import java.util.GregorianCalendar;
import java.util.List;


import org.hibernate.Query;
import org.hibernate.Session;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.orm.hibernate3.HibernateTransactionManager;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class AudioTest extends AbstractDependencyInjectionSpringContextTests
 {
	
	private final static Logger LOGGER = LoggerFactory.getLogger(AudioTest.class);	

	private Audio audio;
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTransactionManager txManager;

	public void setTxManager(HibernateTransactionManager txManager_) {
		txManager = txManager_;
	}

	public void setAudio(Audio audioDao) {
		this.audio = audioDao;
	}

	
	@SuppressWarnings("unchecked")
	@Test
	public void testSimpleRetrieve() {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		Session session = txManager.getSessionFactory().getCurrentSession();
		Query query = session.createQuery("from Audio where fileID=1");
		Audio audio = (Audio) query.uniqueResult();
		
		
		assertNotNull(audio);
		assertEquals("Hello", audio.getTitle());
		txManager.commit(ts);
	}
	
	
	@Test
	public void testSimpleInsert() {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		User user = new User();
		user.setEnabled(true);
		user.setGhost(false);
		user.setGroups(null);
		user.setLastUpdated(GregorianCalendar.getInstance());
		user.setUserID(new Long(29));
		user.setUsername("Your mum");
		
		audio.setCreator(user);
		
		Session session = txManager.getSessionFactory().getCurrentSession();
		audio.setParent(getRootDir(session));
		session.save(audio);
		assertEquals("Check the set audio title", "All the small things",audio.getTitle());
		assertNotNull("Check audio id has been assigned", audio.getFileID());
		
		txManager.commit(ts);
	}
	
	private static File getRootDir(Session session) {
		Query query = session.createQuery("from File where fileID=0");
		return (File) query.uniqueResult();
	}
}
