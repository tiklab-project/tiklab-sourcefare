package io.tiklab.sourcefare.project.controller;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.scan.model.ScanRule;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.toolkit.context.AppContext;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;


import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;

public class test {

    public static void main(String[] args) throws Exception {
        String a="C:\\Program Files (x86)\\Sourcefare\\embbed\\result\\4fe97d14cb25-pmd-issue.xml";
        String b = String.format("\"%s\"", a);

        System.out.println(a);
        System.out.println(b);
    }

}
