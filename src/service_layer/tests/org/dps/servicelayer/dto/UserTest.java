package org.dps.servicelayer.dto;

import java.util.List;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;

public class UserTest extends AbstractDependencyInjectionSpringContextTests {
	
	private final static Logger LOGGER = LoggerFactory.getLogger(UserTest.class);
	
	private User user;
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTemplate hibernateTemplate;
	
	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
		this.hibernateTemplate = hibernateTemplate;
	}

	public void setUser(User userDao) {
		this.user = userDao;
	}
	
	@Test
	public void testSimpleRetrieval() {
		List<User> aList = (List<User>) hibernateTemplate.find("from User where userID=1");
		
		LOGGER.debug("User name retrieved: " + aList.get(0).toString());
		
		assertNotNull("Not null check", aList);
	}
}
