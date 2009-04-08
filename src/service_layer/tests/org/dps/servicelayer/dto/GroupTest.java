package org.dps.servicelayer.dto;

import java.util.List;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;

public class GroupTest extends AbstractDependencyInjectionSpringContextTests{
	private final static Logger LOGGER = LoggerFactory.getLogger(GroupTest.class);
	
	private Group group;
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTemplate hibernateTemplate;
	
	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
		this.hibernateTemplate = hibernateTemplate;
	}

	public void setGroup(Group groupDao) {
		this.group = groupDao;
	}
	
	
	@Test
	public void testSimpleRetrieval() {
		List<Group> aList = (List<Group>) hibernateTemplate.find("from Group where groupID=1");
		
		LOGGER.debug("Group name retrieved: " + aList.get(0).toString());
		
		//LOGGER.debug("First user in group retrieved: " + aList.get(0).getUsers().iterator().next().getUsername());
		
		assertNotNull("Not null check", aList);
	}
}
