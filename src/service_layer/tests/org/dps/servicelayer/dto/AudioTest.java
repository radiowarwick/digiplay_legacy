package org.dps.servicelayer.dto;

import java.util.List;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.orm.hibernate3.SessionFactoryUtils;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;
import org.springframework.test.AbstractTransactionalDataSourceSpringContextTests;

public class AudioTest extends AbstractDependencyInjectionSpringContextTests
 {
	
	final static Logger LOGGER = LoggerFactory.getLogger(AudioTest.class);
	

	private Audio audio;
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTemplate hibernateTemplate;
	
	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
		this.hibernateTemplate = hibernateTemplate;
	}

	public void setAudio(Audio audioDao) {
		this.audio = audioDao;
	}

	
	@SuppressWarnings("unchecked")
	@Test
	public void testSimpleRetrieve() {
		
		List<Audio> aList = (List<Audio>) hibernateTemplate.find("from Audio where audioID=1");
		
		LOGGER.debug(aList.get(0).toString());
		
		assertNotNull(aList);
		assertEquals("More than one result returned",1, aList.size());
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
