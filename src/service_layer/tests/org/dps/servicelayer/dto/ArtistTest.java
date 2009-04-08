package org.dps.servicelayer.dto;

import java.util.List;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;

public class ArtistTest extends AbstractDependencyInjectionSpringContextTests {

	final static Logger LOGGER = LoggerFactory.getLogger(ArtistTest.class);
	
	private Artist artist;
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTemplate hibernateTemplate;
	
	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
		this.hibernateTemplate = hibernateTemplate;
	}

	public void setArtist(Artist artistDao) {
		this.artist = artistDao;
	}
	
	@Test
	public void testSimpleAudioRetrievalTest() {
		List<Artist> aList = (List<Artist>) hibernateTemplate.find("from Artist where artistID=1");
		
		LOGGER.debug("Artist name retrieved: " + aList.get(0).toString());
		
		assertNotNull("Not null check", aList);
		
	}
}
