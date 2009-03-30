package org.dps.servicelayer.dto;

import static org.junit.Assert.*;

import java.util.List;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;

public class AlbumTest extends AbstractDependencyInjectionSpringContextTests {

	final static Logger LOGGER = LoggerFactory.getLogger(AlbumTest.class);
	
	private Album album;
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTemplate hibernateTemplate;
	
	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
		this.hibernateTemplate = hibernateTemplate;
	}

	public void setAlbum(Album albumDao) {
		this.album = albumDao;
	}
	
	@Test
	public void testSimpleAudioRetrievalTest() {
		List<Album> aList = (List<Album>) hibernateTemplate.find("from Album where albumID=2");
		
		LOGGER.debug("Album name retrieved: " + aList.get(0).toString());
		
		assertNotNull("Not null check", aList);
		
	}
}
