package org.dps.servicelayer.dto;

import java.util.List;

import javax.transaction.NotSupportedException;
import javax.transaction.SystemException;
import javax.transaction.TransactionManager;

import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.orm.hibernate3.HibernateTransactionManager;
import org.springframework.orm.hibernate3.SessionFactoryUtils;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;
import org.springframework.test.AbstractTransactionalDataSourceSpringContextTests;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class CartsetTest extends AbstractDependencyInjectionSpringContextTests
 {
	
	final static Logger LOGGER = LoggerFactory.getLogger(CartsetTest.class);
	

	private Audio audio;
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTemplate hibernateTemplate;
	private HibernateTransactionManager txManager;
	
	public HibernateTransactionManager getTxManager() {
		return txManager;
	}

	public void setTxManager(HibernateTransactionManager txManager_) {
		txManager = txManager_;
	}

	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
		this.hibernateTemplate = hibernateTemplate;
	}

	public void setAudio(Audio audioDao) {
		this.audio = audioDao;
	}

	
	@SuppressWarnings("unchecked")
	@Test
	public void testShallowRetrieve() {
		
		List<Cartset> cList = (List<Cartset>) hibernateTemplate.find("from Cartset where cartsetID=1");
				
		assertNotNull(cList);
		assertEquals("More than one result returned",1, cList.size());
		LOGGER.debug(cList.get(0).toString());
	}
	
	@SuppressWarnings("unchecked")
	@Test
	public void testDeepRetrieve() throws Exception {
		LOGGER.debug(Boolean.toString(hibernateTemplate.isAllowCreate()));
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		Session session = txManager.getSessionFactory().getCurrentSession();
		Query query = session.createQuery("from Cartset where cartsetID=1");
		List<Cartset> cList = (List<Cartset>) query.list();
				
		assertNotNull(cList);
		assertEquals("More than one result returned",1, cList.size());
		Cartset cartset = cList.get(0);
		LOGGER.debug(cartset.toString());
		assertEquals("Invalid number of cartwalls returned",2, cartset.getCartwalls().size());
		txManager.commit(ts);
	}
	/*
	@Test
	public void testSimpleInsert() {
		Session session = SessionFactoryUtils.doGetSession(hibernateTemplate.getSessionFactory(), true);
		
		Transaction t =  session.beginTransaction();
		try {
		audio.setTitle("All the small things");
		
		hibernateTemplate.saveOrUpdate(audio);
		
		LOGGER.debug("AudioID : " + audio.getAudioID());
		assertNotNull("Check audio id has been assigned", audio.getAudioID());
		assertEquals("Check the set audio title", "All the small things",audio.getTitle());
		
		t.commit();
		} finally {
			if (t.isActive()) {
				t.rollback();
			}
		}

	}
	*/

}
