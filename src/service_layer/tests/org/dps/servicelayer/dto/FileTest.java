package org.dps.servicelayer.dto;

import java.util.List;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;

public class FileTest extends AbstractDependencyInjectionSpringContextTests {

	private final static Logger LOGGER = LoggerFactory.getLogger(FileTest.class);
	
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	
	private File file;
	
	private HibernateTemplate hibernateTemplate;
	
	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
		this.hibernateTemplate = hibernateTemplate;
	}

	public void setFile(File fileDao) {
		this.file = fileDao;
	}
	
	@Test
	public void testSimpleRetrieve() {
		
		List<File> aList = (List<File>) hibernateTemplate.find("from File where fileID=1");
		
		LOGGER.debug("Child: " + aList.get(0).toString());
		
		//LOGGER.debug("Parent: " + aList.get(0).getParent().getName().toString());
		
		assertNotNull(aList);
		assertEquals("More than one result returned",1, aList.size());
	}
	
}
